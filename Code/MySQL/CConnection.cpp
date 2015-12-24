#include <MySQL/CConnection.hpp>
#include <Log/CLog.hpp>

CConnection::CConnection(const std::string& Host, const std::string& Database, const std::string& Username, const std::string& Password, const uint32_t Port)
	: m_connection(nullptr)
	, m_shouldStop(false)
{
	CLog::GetInstance()->Log(LogLevel::kDebug, "CConnection::CConnection(this={}, host='{}', database='{}', user='{}', password='****', port='{}')", static_cast<const void*>(this), Host.c_str(),
		Database.c_str(), Username.c_str(), Port);

	m_connection = mysql_init(nullptr);

	if (m_connection == nullptr)
	{
		CLog::GetInstance()->Log(LogLevel::kError, "CConnection::CConnection - MySQL initialization failed");

		return;
	}

	if (mysql_real_connect(m_connection, Host.c_str(), Username.c_str(), Password.c_str(), Database.c_str(), Port, NULL, 0))
	{
		my_bool bReconnect = true;
		mysql_options(m_connection, MYSQL_OPT_RECONNECT, &bReconnect);

		m_thread = std::make_unique<std::thread>(std::bind(&CConnection::ProcessQueries, this));

		CLog::GetInstance()->Log(LogLevel::kDebug, "CConnection::CConnection - new connection = {}", static_cast<const void*>(m_connection));
	}
	else
	{
		CLog::GetInstance()->Log(LogLevel::kError, "CConnection::CConnection- error #{} ({})", mysql_errno(m_connection), mysql_error(m_connection));
	}
}

CConnection::~CConnection()
{
	CLog::GetInstance()->Log(LogLevel::kDebug, "CConnection::~CConnection(this={})", static_cast<const void*>(this));

	if (m_connection != nullptr)
	{
		bool IsEmpty = false;

		while (IsEmpty == false)
		{
			m_queryMutex.lock();
			IsEmpty = m_queryQueue.empty();
			m_queryMutex.unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		m_shouldStop.store(true);
		m_thread->join();

		mysql_close(m_connection);
	}
}

void CConnection::ProcessCallbacks()
{
	std::lock_guard<std::mutex> lock_guard(m_callbackMutex);

	if (m_callbackQueue.empty() == false)
	{
		while (m_callbackQueue.empty() == false)
		{
			auto Callback = std::move(m_callbackQueue.front());
			m_callbackQueue.pop();

			// Call the callback.
			Callback();
		}
	}
}

void CConnection::Queue(std::shared_ptr<CQuery> Query, std::function<void()> Callback, std::shared_ptr<CResult> Result)
{
	auto Element = std::make_tuple(std::move(Query), std::move(Callback), std::move(Result));

	std::lock_guard<std::mutex> lock_guard(m_queryMutex);
	m_queryQueue.push(Element);
}

void CConnection::ProcessQueries()
{
	mysql_thread_init();

	while (m_shouldStop.load(std::memory_order::memory_order_acquire) == false)
	{
		m_queryMutex.lock();

		try
		{
			// Check if queue has elements.
			if (m_queryQueue.empty() == false)
			{
				while (m_queryQueue.empty() == false)
				{
					auto Query = std::move(std::get<0>(m_queryQueue.front()));
					auto Callback = std::move(std::get<1>(m_queryQueue.front()));

					// We can move the result because it will have more than one uses because it is used with std::bind for the function.
					auto Result = std::move(std::get<2>(m_queryQueue.front()));

					m_queryQueue.pop();

					for (auto& Parameter : Query->GetParameters())
					{
						size_t Length = Parameter.GetValue().length();

						char* TemporaryChar = static_cast<char*>(malloc((Length * 2 + 1) * sizeof(char)));
						mysql_real_escape_string(m_connection, TemporaryChar, Parameter.GetValue().c_str(), Length);

						std::string EscapedString(TemporaryChar);
						free(TemporaryChar);

						size_t Position = Query->GetQuery().find(Parameter.GetName());

						if (Position != std::string::npos)
						{
							Query->Replace(Position, Parameter.GetName().length(), EscapedString);
						}
						else
						{
							CLog::GetInstance()->Log(LogLevel::kError, "CConnection::Process(this={}) - Cannot find parameter \\\"{}\\\" to bind it", static_cast<const void*>(m_connection), 
								Parameter.GetName());
						}
					}

					if (mysql_real_query(m_connection, Query->c_str(), Query->length()) != 0)
					{
						CLog::GetInstance()->Log(LogLevel::kError, "CConnection::Process(this={}) - Error (#{}) at executing query \\\"{}\\\"<br />({})", static_cast<const void*>(m_connection), 
							mysql_errno(m_connection), Query->GetQuery(), mysql_error(m_connection));

						continue;
					}

					CLog::GetInstance()->Log(LogLevel::kDebug, "CConnection::Process(this={}) - query \\\"{}\\\" successfully executed", static_cast<const void*>(m_connection), Query->GetQuery());

					// Check if the query has a callback and queue it for call.
					if (Callback != nullptr)
					{
						MYSQL_RES* StoredResult = mysql_store_result(m_connection);

						if (StoredResult != nullptr) // It is a SELECT query.
						{
							MYSQL_FIELD* Field;
							MYSQL_ROW Row;

							size_t RowIndex = 0;

							Result->m_fieldsCount = mysql_num_fields(StoredResult);
							Result->m_rowsCount = mysql_num_rows(StoredResult);

							// Set the capacity of the vector.
							Result->m_fields.reserve(Result->m_fieldsCount);
							
							// Let's store the fields name.
							while ((Field = mysql_fetch_field(StoredResult)))
							{
								FieldInformation CurrentField;
								CurrentField.Name = Field->name;
								CurrentField.Type = Field->type;

								Result->m_fields.push_back(CurrentField);
							}

							// Resize the vector for rows.
							Result->m_data.resize(static_cast<size_t>(Result->m_rowsCount));

							for (size_t i = 0; i < Result->m_rowsCount; i++)
							{
								// Resize the vector for columns.
								Result->m_data[i].resize(Result->m_fieldsCount);

								// Fill the array with data.
								Row = mysql_fetch_row(StoredResult);

								for (size_t j = 0; j < Result->m_fieldsCount; j++)
								{
									// Check if the field is null.
									Result->m_data[i][j] = Row[j] != NULL ? Row[j] : "";
								}
							}

							mysql_free_result(StoredResult);
						}
						else // It isn't a SELECT query.
						{
							if (mysql_field_count(m_connection) == 0)
							{
								Result->m_affectedRows = mysql_affected_rows(m_connection);
								Result->m_insertID = mysql_insert_id(m_connection);
								Result->m_warningCount = mysql_warning_count(m_connection);
							}
						}

						m_callbackMutex.lock();
						m_callbackQueue.push(std::move(Callback));
						m_callbackMutex.unlock();
					}
				}
			}
		}
		catch (std::exception e)
		{
			CLog::GetInstance()->Log(LogLevel::kError, "CConnection::Process - exception {}", e.what());
		}

		m_queryMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	mysql_thread_end();
}

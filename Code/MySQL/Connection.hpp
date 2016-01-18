#pragma once

class Connection
{
public:

	Connection(const std::string& Host, const std::string& Database, const std::string& Username, const std::string& Password, const uint16_t Port = MYSQL_PORT);
	~Connection();

	void ProcessCallbacks();

	void Queue(std::shared_ptr<Query> Query, std::function<void()> Callback, std::shared_ptr<MySQLResult> Result);

private:

	void ProcessQueries();

	MYSQL* m_connection;

	std::unique_ptr<std::thread> m_thread;
	std::atomic<bool> m_shouldStop;

	std::queue<std::tuple<std::shared_ptr<Query>, std::function<void()>, std::shared_ptr<MySQLResult>>> m_queryQueue;
	std::mutex m_queryMutex;

	std::queue<std::function<void()>> m_callbackQueue;
	std::mutex m_callbackMutex;
};
#pragma once

/// <summary>
/// Base class to store an undefined amount of objects with any type.
/// </summary>
template<typename TK>
class Data
{
public:

	Data() = default;
	virtual ~Data() = default;

	/// <summary>
	/// Add data to the list.
	/// </summary>
	/// <param name="Index">Index for the data.</param>
	/// <param name="Value">Value for the data.</param>
	/// <returns>Returns true if the data is added with success, false if already exists.</returns>
	template<typename T>
	inline const bool AddData(TK Index, T Value)
	{
		// Check if the key already exists.
		if (m_data.find(Index) != m_data.end())
		{
			return false;
		}

		m_data.emplace(Index, std::make_shared<Any<T>>(Value));

		return true;
	}

	/// <summary>
	/// Get the value from the list.
	/// </summary>
	/// <param name="Index">Index for the data.</param>
	/// <returns>Returns value of the data if exists, if it doesn't exist returns a new value of specific type.</returns>
	template<typename T>
	inline const T GetData(TK Index) const
	{
		// Check if the key exists, if not return the type.
		if (m_data.find(Index) == m_data.end())
		{
			return T();
		}

		// Return the value at index.
		return dynamic_cast<Any<T>&>(*m_data.at(Index)).Get();
	}

	/// <summary>
	/// Get the size of the list.
	/// </summary>
	/// <returns>Returns size of the list.</returns>
	inline const size_t GetSize() const
	{
		return m_data.size();
	}

	/// <summary>
	/// Set value for an object from the list, detect type. It will add the object if it doesn't exist.
	/// </summary>
	/// <param name="Field">Field information.</param>
	/// <param name="Index">Index for the data.</param>
	/// <param name="Value">Value for the data.</param>
	inline const void SetData(FieldInformation Field, TK Index, std::string Value)
	{
		if (Field.IsNumeric == false)
		{
			SetData<std::string>(Index, Value);
			return;
		}
		else if (Value.length() == 0)
		{
			Value = "0";
		}

		if (Field.IsBool == true)
		{
			SetData<bool>(Index, !!std::stoi(Value));
			return;
		}

		switch (Field.Type)
		{
			case enum_field_types::MYSQL_TYPE_DOUBLE:
			{
				SetData<double>(Index, std::stod(Value));
				break;
			}
			case enum_field_types::MYSQL_TYPE_FLOAT:
			{
				SetData<float>(Index, std::stof(Value));
				break;
			}
			case enum_field_types::MYSQL_TYPE_INT24:
			case enum_field_types::MYSQL_TYPE_LONG:
			{
				if (Field.IsUnsigned == true)
				{
					SetData<uint32_t>(Index, std::stoul(Value));
				}
				else
				{
					SetData<int32_t>(Index, std::stoi(Value));
				}

				break;
			}
			case enum_field_types::MYSQL_TYPE_LONGLONG:
			{
				if (Field.IsUnsigned == true)
				{
					SetData<uint64_t>(Index, std::stoull(Value));
				}
				else
				{
					SetData<int64_t>(Index, std::stoll(Value));
				}

				break;
			}
			case enum_field_types::MYSQL_TYPE_SHORT:
			{
				if (Field.IsUnsigned == true)
				{
					SetData<uint16_t>(Index, std::stoi(Value));
				}
				else
				{
					SetData<int16_t>(Index, std::stoi(Value));
				}

				break;
			}
			case enum_field_types::MYSQL_TYPE_TINY:
			{
				if (Field.IsUnsigned == true)
				{
					SetData<uint8_t>(Index, std::stoi(Value));
				}
				else
				{
					SetData<int8_t>(Index, std::stoi(Value));
				}

				break;
			}
		}
	}

	/// <summary>
	/// Set value for an object from the list. It will add the object if it doesn't exist.
	/// </summary>
	/// <param name="Index">Index for the data.</param>
	/// <param name="Value">Value for the data.</param>
	template<typename T>
	inline const void SetData(TK Index, T Value)
	{
		// Check if the key exists, if not add it.
		if (m_data.find(Index) == m_data.end())
		{
			AddData(Index, Value);
		}
		else
		{
			// Set the new value.
			auto Data = dynamic_cast<Any<T>*>(m_data.at(Index).get());
			Data->Set(Value);
		}
	}

private:

	std::unordered_map<TK, std::shared_ptr<AnyObject>> m_data;
};
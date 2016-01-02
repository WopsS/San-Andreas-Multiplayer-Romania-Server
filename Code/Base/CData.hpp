#pragma once

/// <summary>
/// Base class to store an undefined amount of objects with any type.
/// </summary>
template<typename TK>
class CData
{
public:

	CData() { };
	virtual ~CData() { };

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

		m_data.emplace(Index, std::make_shared<CAny<T>>(Value));

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
		return dynamic_cast<CAny<T>&>(*m_data.at(Index)).Get();
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
			auto Any = dynamic_cast<CAny<T>*>(m_data.at(Index).get());
			Any->Set(Value);
		}
	}

private:

	std::unordered_map<TK, std::shared_ptr<CObject>> m_data;
};
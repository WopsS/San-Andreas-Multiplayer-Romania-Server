#pragma once

#include <memory>
#include <unordered_map>

#include <Base/CAny.hpp>

/// <summary>
/// Base class to store an undefined amount of objects with any type.
/// </summary>
template <typename TK>
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
	/// <returns>Returns true if the data is added with success, false if it already exists.</returns>
	template<typename T>
	inline const bool AddData(TK Index, T Value)
	{
		// Check if the key already exists.
		if (m_data.find(Index) != m_data.end())
		{
			return false;
		}

		m_data.insert(std::make_pair(Index, std::make_unique<CAny<T>>(Value)));

		return true;
	}

	/// <summary>
	/// Get the object value from the list.
	/// </summary>
	/// <param name="Index">Index for the data.</param>
	/// <returns>Returns value of the data if it exist, if it doesn't exist returns a new value of specific type.</returns>
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
			AddData(Index, T());
		}

		// Set the new value.
		auto Any = dynamic_cast<CAny<T>*>(m_data.at(Index).get());
		Any->Set(Value);
	}

private:

	std::unordered_map<TK, std::unique_ptr<CObject>> m_data;
};
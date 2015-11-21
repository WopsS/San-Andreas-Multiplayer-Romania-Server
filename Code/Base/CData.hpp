#pragma once

#include <unordered_map>

#include <Base/CAny.hpp>

template <typename TK>
class CData
{
public:

	CData() { };
	virtual ~CData() { };

	template<typename T>
	inline const bool Add(TK Index, T Value)
	{
		// Check if the key already exists.
		if (m_data.find(Index) != m_data.end())
		{
			return false;
		}

		m_data.insert(std::make_pair(Index, std::make_unique<CAny<T>>(Value)));

		return true;
	}

	template<typename T>
	inline const T Get(TK Index)
	{
		// Check if the key exists, if not add it.
		if (m_data.find(Index) == m_data.end())
		{
			Add(Index, T());
		}

		// Return the value at index.
		return dynamic_cast<CAny<T>&>(*m_data.at(Index)).Get();
	}

	template<typename T>
	inline const bool Set(TK Index, T Value)
	{
		// Check if the key exists, if not add it.
		if (m_data.find(Index) == m_data.end())
		{
			Add(Index, T());
		}

		// Set the new value.
		auto Any = dynamic_cast<CAny<T>*>(m_data.at(Index).get());
		Any->Set(Value);

		return true;
	}

private:

	std::unordered_map<TK, std::unique_ptr<CObject>> m_data;
};
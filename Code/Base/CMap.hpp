#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

template<class T>
class CMap
{
public:

	CMap() { };
	virtual ~CMap() { };

	inline static bool Add(uint16_t ID)
	{
		// Check if the key already exists.
		if (m_list.find(ID) != m_list.end())
		{
			return false;
		}

		m_list.insert(std::make_pair(ID, std::make_shared<T>(ID)));

		return true;
	}

	inline static std::shared_ptr<T> Get(uint16_t ID)
	{
		// Check if the key exists. 
		if (m_list.find(ID) == m_list.end())
		{
			return nullptr;
		}

		return m_list.at(ID);
	}

	inline static bool Remove(uint16_t ID)
	{
		// Check if the key exists.
		if (m_list.find(ID) == m_list.end())
		{
			return false;
		}

		m_list.erase(ID);

		return true;
	}

private:

	static std::unordered_map<uint16_t, std::shared_ptr<T>> m_list;
};

template <class T>
std::unordered_map<uint16_t, std::shared_ptr<T>> CMap<T>::m_list;
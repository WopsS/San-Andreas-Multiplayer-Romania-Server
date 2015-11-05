#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

template<class T>
class CMap
{
public:

	CMap() {  };
	virtual ~CMap() { };

	inline static bool Add(uint16_t ID)
	{
		// Check if the key already exists.
		if (m_pList.find(ID) != m_pList.end())
		{
			return false;
		}

		m_pList.insert(std::make_pair(ID, std::make_shared<T>(ID)));

		return true;
	}

	inline static std::shared_ptr<T> Get(uint16_t ID)
	{
		// Check if the key exists. 
		if (m_pList.find(ID) == m_pList.end())
		{
			return nullptr;
		}

		return m_pList.at(ID);
	}

	inline static bool Remove(uint16_t ID)
	{
		// Check if the key exists.
		if (m_pList.find(ID) == m_pList.end())
		{
			return false;
		}

		m_pList.erase(ID);

		return true;
	}

private:

	static std::unordered_map<uint16_t, std::shared_ptr<T>> m_pList;
};

template <class T>
std::unordered_map<uint16_t, std::shared_ptr<T>> CMap<T>::m_pList;
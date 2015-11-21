#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include <Base/CAny.hpp>

template<typename T, class C>
class CMap
{
public:

	CMap() { };
	virtual ~CMap() { };

	template<typename... Args>
	inline static bool Add(T ID, Args&& ...args)
	{
		// Check if the key already exists.
		if (m_list.find(ID) != m_list.end())
		{
			return false;
		}

		m_list.insert(std::make_pair(ID, std::make_shared<C>(ID, std::forward<Args>(args)...)));

		return true;
	}

	inline static std::shared_ptr<C> Get(T ID)
	{
		// Check if the key exists. 
		if (m_list.find(ID) == m_list.end())
		{
			return nullptr;
		}

		return m_list.at(ID);
	}

	inline static bool Remove(T ID)
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

	static std::unordered_map<T, std::shared_ptr<C>> m_list;
};

template<typename T, class C>
std::unordered_map<T, std::shared_ptr<C>> CMap<T, C>::m_list;
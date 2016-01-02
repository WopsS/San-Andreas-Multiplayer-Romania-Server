#pragma once

/// <summary>
/// Base class to store an undefined amount of objects with the same type.
/// </summary>
template<typename T, class C>
class CMap
{
public:

	CMap() { };
	virtual ~CMap() { };

	/// <summary>
	/// Add an object to the list.
	/// </summary>
	/// <param name="Index">Index for the object.</param>
	/// <param name="args">Undefined number of arguments for the object constructor.</param>
	/// <returns>Returns true if the object is added with success, false if it already exists.</returns>
	template<typename... Args>
	inline static bool Add(T Index, Args&& ...args)
	{
		// Check if the key already exists.
		if (m_list.find(Index) != m_list.end())
		{
			return false;
		}

		m_list.emplace(Index, std::make_shared<C>(Index, std::forward<Args>(args)...));

		return true;
	}

	/// <summary>
	/// Check if an object exist in list.
	/// </summary>
	/// <param name="Index">Index for the object.</param>
	/// <returns>Returns true if the object exists, false otherwise.</returns>
	inline static bool Contains(T Index)
	{
		return m_list.find(Index) != m_list.end();
	}

	/// <summary>
	/// Get the object from the list.
	/// </summary>
	/// <param name="Index">Index of an object.</param>
	/// <returns>Returns value of the object if it exist, if it doesn't exist returns nullptr.</returns>
	inline static std::shared_ptr<C> Get(T Index)
	{
		// Check if the key exists. 
		if (m_list.find(Index) == m_list.end())
		{
			return nullptr;
		}

		return m_list.at(Index);
	}

	/// <summary>
	/// Get the list of the objects.
	/// </summary>
	/// <returns>Returns list of the objects.</returns>
	inline static std::unordered_map<T, std::shared_ptr<C>> GetList()
	{
		return m_list;
	}

	/// <summary>
	/// Remove an object from the list.
	/// </summary>
	/// <param name="Index">Index of an object.</param>
	/// <returns>Returns true if it is removed with success, false otherwise.</returns>
	inline static bool Remove(T Index)
	{
		// Check if the key exists.
		if (m_list.find(Index) == m_list.end())
		{
			return false;
		}

		m_list.erase(Index);

		return true;
	}

private:

	static std::unordered_map<T, std::shared_ptr<C>> m_list;
};

template<typename T, class C>
std::unordered_map<T, std::shared_ptr<C>> CMap<T, C>::m_list;
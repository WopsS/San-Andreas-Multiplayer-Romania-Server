#pragma once

/// <summary>
/// Base class for singletons.
/// </summary>
template<class T>
class Singleton
{
public:

	/// <summary>
	/// Destroy instance of the singleton.
	/// </summary>
	/// <returns>Returns true if the instance exists and it is deleted, false otherwise.</returns>
	inline static bool DestroyInstance()
	{
		// Check if we have a valid instance.
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;

			return true;
		}

		return false;
	}

	/// <summary>
	/// Get instance of the singleton.
	/// </summary>
	/// <returns>Returns a pointer to the instance of the singleton.</returns>
	inline static T* GetInstance()
	{
		// Check if the instance is already allocated.
		if (m_instance == nullptr)
		{
			m_instance = new T();
		}

		return m_instance;
	}

protected:

	Singleton() = default;
	virtual ~Singleton() = default;

private:

	static T* m_instance;
};

template<class T>
T* Singleton<T>::m_instance = nullptr;
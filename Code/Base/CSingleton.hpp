#pragma once

template<class T>
class CSingleton
{
public:

	CSingleton() { };
	virtual ~CSingleton() { };

	inline static void DestroyInstance()
	{
		// Check if we have a valid instance.
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	inline static T* GetInstance()
	{
		// Check if the instance is already allocated.
		if (m_instance == nullptr)
		{
			m_instance = new T();
		}

		return m_instance;
	}

private:

	static T* m_instance;
};

template<class T>
T* CSingleton<T>::m_instance = nullptr;
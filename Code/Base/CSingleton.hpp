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
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	inline static T* GetInstance()
	{
		// Check if the instance is already allocated.
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}

private:

	static T* m_pInstance;
};

template <class T>
T* CSingleton<T>::m_pInstance = nullptr;
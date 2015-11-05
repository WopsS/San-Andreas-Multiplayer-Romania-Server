#pragma once

template<class T>
class CSingleton
{
public:

	CSingleton() { };
	virtual ~CSingleton() { };

	inline static void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	inline static T* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}

protected:

	static T* m_pInstance;
};

template <class T>
T* CSingleton<T>::m_pInstance = nullptr;
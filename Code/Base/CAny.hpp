#pragma once

class CObject
{
public:

	CObject() { };
	virtual ~CObject() { };
};

template<typename T>
class CAny : public CObject
{
public:

	CAny(T Value) : m_value(Value) { };
	~CAny() { };

	inline const T Get() const
	{
		return m_value;
	}

	inline void Set(T Value)
	{
		m_value = Value;
	}

private:

	T m_value;
};

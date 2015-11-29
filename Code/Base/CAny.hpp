#pragma once

/// <summary>
/// Base class for <see cref="CAny"/> objects.
/// </summary>
class CObject
{
public:

	CObject() { };
	virtual ~CObject() { };
};

/// <summary>
/// Class which can store any type of objects.
/// </summary>
template<typename T>
class CAny : public CObject
{
public:

	/// <summary>
	/// Class constructor.
	/// </summary>
	/// <param name="Value">Value for the object.</param>
	CAny(T Value) : m_value(Value) { };
	~CAny() { };

	/// <summary>
	/// Get value of the object.
	/// </summary>
	/// <returns>Returns value of the object.</returns>
	inline const T Get() const
	{
		return m_value;
	}
		
	/// <summary>
	/// Set value for the object.
	/// </summary>
	/// <param name="Value">New value for the object.</param>
	inline void Set(T Value)
	{
		m_value = Value;
	}

private:

	T m_value;
};
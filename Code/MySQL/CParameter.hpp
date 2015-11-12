#pragma once

#include <string>

class CParameter
{
public:

	CParameter(const std::string& Name, const std::string& Value);
	~CParameter();

	inline const std::string& GetName() const
	{
		return m_name;
	}

	inline const std::string& GetValue() const
	{
		return m_value;
	}

private:

	std::string m_name;

	std::string m_value;
};
#include <MySQL/Parameter.hpp>

MySQLParameter::MySQLParameter(const std::string& Name, const std::string& Value)
	: m_name(Name)
	, m_value(Value)
{
}
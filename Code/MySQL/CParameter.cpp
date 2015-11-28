#include <MySQL/CParameter.hpp>

CParameter::CParameter(const std::string& Name, const std::string& Value) 
	: m_name(Name)
	, m_value(Value)
{
}
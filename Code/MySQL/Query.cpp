#include <MySQL/Query.hpp>

Query::Query(const QueryType Type, const std::string& Query, std::initializer_list<MySQLParameter> Parameters)
	: m_type(Type)
	, m_query(Query)
	, m_parameters(Parameters)
{
}

const char* Query::c_str() const
{
	return m_query.c_str();
}

const std::vector<MySQLParameter>& Query::GetParameters() const
{
	return m_parameters;
}

const std::string& Query::GetQuery() const
{
	return m_query;
}

const QueryType& Query::GetType() const
{
	return m_type;
}

size_t Query::length() const
{
	return m_query.length();
}

void Query::Replace(size_t Position, size_t Length, std::string Text)
{
	m_query.replace(Position, Length, Text);
}

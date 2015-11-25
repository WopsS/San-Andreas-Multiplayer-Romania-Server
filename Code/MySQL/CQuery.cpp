#include <MySQL/CQuery.hpp>

CQuery::CQuery(const QueryType& Type, const std::string& Query, std::initializer_list<CParameter> Parameters)
	: m_type(Type)
	, m_query(Query)
	, m_parameters(Parameters)
{
}

CQuery::~CQuery()
{
}

const char* CQuery::c_str() const
{
	return m_query.c_str();
}

const std::vector<CParameter>& CQuery::GetParameters() const
{
	return m_parameters;
}

const std::string& CQuery::GetQuery() const
{
	return m_query;
}

const QueryType& CQuery::GetType() const
{
	return m_type;
}

size_t CQuery::length() const
{
	return m_query.length();
}

void CQuery::Replace(size_t Position, size_t Length, std::string Text)
{
	m_query.replace(Position, Length, Text);
}

#pragma once

enum QueryType : uint16_t
{
	kNormal = 1,
	kLog
};

class Query
{
public:

	Query(const QueryType& Type, const std::string& Query, std::initializer_list<MySQLParameter> Parameters);
	~Query() = default;

	const char* c_str() const;

	const std::vector<MySQLParameter>& GetParameters() const;

	const std::string& GetQuery() const;

	const QueryType& GetType() const;

	size_t length() const;

	void Replace(size_t Position, size_t Length, std::string Text);

private:

	QueryType m_type;

	std::string m_query;

	std::vector<MySQLParameter> m_parameters;
};
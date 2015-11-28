#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <MySQL/CParameter.hpp>
#include <MySQL/CResult.hpp>

enum QueryType : uint16_t
{
	kNormal = 1,
	kLog
};

class CQuery
{
public:

	CQuery(const QueryType& Type, const std::string& Query, std::initializer_list<CParameter> Parameters);
	~CQuery() = default;

	const char* c_str() const;

	const std::vector<CParameter>& GetParameters() const;

	const std::string& GetQuery() const;

	const QueryType& GetType() const;

	size_t length() const;

	void Replace(size_t Position, size_t Length, std::string Text);

private:

	QueryType m_type;

	std::string m_query;

	std::vector<CParameter> m_parameters;
};
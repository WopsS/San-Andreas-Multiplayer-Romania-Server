#include <MySQL/CMySQL.hpp>

CMySQL::CMySQL()
	: m_connectionPool(std::make_unique<CConnectionPool>(5))
{
}

void CMySQL::ProcessCallbacks()
{
	m_connectionPool->ProcessCallbacks();
}
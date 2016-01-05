#include <MySQL/MySQL.hpp>

MySQL::MySQL()
	: m_connectionPool(std::make_unique<ConnectionPool>(5))
{
}

void MySQL::ProcessCallbacks()
{
	m_connectionPool->ProcessCallbacks();
}
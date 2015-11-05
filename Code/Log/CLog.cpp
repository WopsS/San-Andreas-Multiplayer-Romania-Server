#include <Log/CLog.hpp>

CLog::CLog()
{
	m_file.open("server_log.html", std::ios::out);
}

CLog::~CLog()
{
	m_file.close();
}

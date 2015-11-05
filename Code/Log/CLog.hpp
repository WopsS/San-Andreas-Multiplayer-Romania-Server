#pragma once

#include <cstdint>
#include <fstream>

#include <format.h>
#include <Base/CSingleton.hpp>

enum LogLevel : uint16_t
{
	kDebug = 1,
	kWarning,
	kError
};

class CLog : public CSingleton<CLog>
{
public:

	template<typename... Args>
	inline void Log(const LogLevel& Level, const std::string& Format, Args&& ...args)
	{
		// TODO: Create a class to store log information.
	}

private:

	friend class CSingleton<CLog>;

	CLog();
	~CLog();

	std::fstream m_file;
};
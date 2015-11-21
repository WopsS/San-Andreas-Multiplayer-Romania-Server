#pragma once

#include <atomic>
#include <cstdint>
#include <fstream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

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
		auto Information = std::make_unique<LogInformation>();

		Information->Level = Level;
		Information->Message = fmt::format(Format, std::forward<Args>(args)...);

		std::lock_guard<std::mutex> lock_guard(m_queueMutex);
		m_queue.push(std::move(Information));
	}

private:

	friend class CSingleton<CLog>;

	CLog();
	~CLog();

	void Process();

	struct LogInformation
	{
		LogLevel Level;
		std::string Message;
	};

	std::fstream m_file;

	std::unique_ptr<std::thread> m_thread;
	std::atomic<bool> m_shouldStop;

	std::queue<std::unique_ptr<LogInformation>> m_queue;
	std::mutex m_queueMutex;
};
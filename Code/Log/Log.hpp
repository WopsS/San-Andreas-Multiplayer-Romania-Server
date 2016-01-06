#pragma once

enum LogLevel : unsigned char
{
	kDebug = 0,
	kWarning,
	kError
};

class Logger : public Singleton<Logger>
{
public:

	template<typename... Args>
	inline void Log(const LogLevel& Level, const std::string& Format, Args&& ...args)
	{
		LogInformation Information;

		Information.Level = Level;
		Information.Message = fmt::format(Format, std::forward<Args>(args)...);

		std::lock_guard<std::mutex> lock_guard(m_queueMutex);
		m_queue.push(Information);
	}

private:

	friend class Singleton<Logger>;

	Logger();
	~Logger();

	void Process();

	struct LogInformation
	{
		LogLevel Level;
		std::string Message;
	};

	std::fstream m_file;

	std::unique_ptr<std::thread> m_thread;
	std::atomic<bool> m_shouldStop;

	std::queue<LogInformation> m_queue;
	std::mutex m_queueMutex;
};
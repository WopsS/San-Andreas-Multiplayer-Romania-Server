#pragma once

enum LogLevel : uint16_t
{
	kDebug = 1,
	kWarning,
	kError
};

class Logger : public Singleton<Logger>
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

	std::queue<std::unique_ptr<LogInformation>> m_queue;
	std::mutex m_queueMutex;
};
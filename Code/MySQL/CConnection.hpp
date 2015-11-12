#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <tuple>

#include <mysql.h>
#include <MySQL/CQuery.hpp>
#include <MySQL/CResult.hpp>

class CConnection
{
public:

	CConnection(const std::string& Host, const std::string& Database, const std::string& Username, const std::string& Password, const uint32_t Port = MYSQL_PORT);
	~CConnection();

	void ProcessCallbacks();

	void Queue(std::shared_ptr<CQuery> Query, std::function<void()> Callback, std::shared_ptr<CResult> Result);

private:

	void ProcessQueries();

	MYSQL* m_connection;

	std::unique_ptr<std::thread> m_thread;
	std::atomic<bool> m_shouldStop;

	std::queue<std::tuple<std::shared_ptr<CQuery>, std::function<void()>, std::shared_ptr<CResult>>> m_queryQueue;
	std::mutex m_queryMutex;

	std::queue<std::function<void()>> m_callbackQueue;
	std::mutex m_callbackMutex;
};
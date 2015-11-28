#pragma once

#include <functional>
#include <memory>

#include <Base/CSingleton.hpp>
#include <MySQL/CConnectionPool.hpp>
#include <MySQL/CParameter.hpp>
#include <MySQL/CQuery.hpp>
#include <MySQL/CResult.hpp>

class CMySQL : public CSingleton<CMySQL>
{
public:

	template<typename T>
	inline CParameter MakeParameter(const std::string& Name, const T& Value)
	{
		std::stringstream StringStream;
		StringStream << Value;

		return CParameter(":" + Name, StringStream.str());
	}

	void ProcessCallbacks();

	inline void Query(const QueryType& Type, std::string Query, std::initializer_list<CParameter> Parameters)
	{
		m_connectionPool->Queue(std::make_shared<CQuery>(Type, Query, Parameters), nullptr, nullptr);
	}

	template<typename F, typename C, typename... Args>
	inline void Query(const QueryType& Type, const std::string& Query, std::initializer_list<CParameter> Parameters, F Function, C Class, Args&&... args)
	{
		auto Result = std::make_shared<CResult>();

		std::function<void()> Callback = std::bind(Function, Class, Result, std::forward<Args>(args)...);
		m_connectionPool->Queue(std::make_shared<CQuery>(Type, Query, Parameters), std::move(Callback), std::move(Result));
	}

private:

	friend class CSingleton<CMySQL>;

	CMySQL();
	~CMySQL() = default;
	
	std::unique_ptr<CConnectionPool> m_connectionPool;
};
#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <Base/CSingleton.hpp>
#include <MySQL/CConnectionPool.hpp>
#include <MySQL/CParameter.hpp>
#include <MySQL/CQuery.hpp>
#include <MySQL/CResult.hpp>

class CMySQL : public CSingleton<CMySQL>
{
public:

	template <typename T>
	inline CParameter MakeParameter(const std::string& Name, const T& Value)
	{
		return CParameter(":" + Name, typeid(Value) == typeid(std::string) ? Value : std::string(Value));
	}

	void ProcessCallbacks();

	inline void Query(const QueryType& Type, std::string Query, const std::vector<CParameter>& Parameters)
	{
		m_connectionPool->Queue(std::make_shared<CQuery>(Type, Query, Parameters), nullptr, nullptr);
	}

	template <typename C, typename F, typename... Args>
	inline void Query(const QueryType& Type, std::string Query, const std::vector<CParameter>& Parameters, std::shared_ptr<C> Class, F Function, Args&&... args)
	{
		auto Result = std::make_shared<CResult>();

		std::function<void()> Callback = std::bind(Function, Class, Result, std::forward<Args>(args)...);
		m_connectionPool->Queue(std::make_shared<CQuery>(Type, Query, Parameters), std::move(Callback), std::move(Result));
	}

private:

	friend class CSingleton<CMySQL>;

	CMySQL();
	~CMySQL();
	
	std::unique_ptr<CConnectionPool> m_connectionPool;
};
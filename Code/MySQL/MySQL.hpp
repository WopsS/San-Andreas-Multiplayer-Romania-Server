#pragma once

class MySQL : public Singleton<MySQL>
{
public:

	template<typename T>
	inline MySQLParameter MakeParameter(const std::string& Name, const T& Value)
	{
		std::stringstream StringStream;
		StringStream << Value;

		return MySQLParameter(":" + Name, StringStream.str());
	}

	void ProcessCallbacks();

	inline void Query(const QueryType& Type, std::string Format, std::initializer_list<MySQLParameter> Parameters)
	{
		m_connectionPool->Queue(std::make_shared<::Query>(Type, Format, Parameters), nullptr, nullptr);
	}

	template<typename F, typename C, typename... Args>
	inline void Query(const QueryType& Type, const std::string& Format, std::initializer_list<MySQLParameter> Parameters, F Function, C Class, Args&&... args)
	{
		auto Result = std::make_shared<MySQLResult>();

		std::function<void()> Callback = std::bind(Function, Class, Result, std::forward<Args>(args)...);
		m_connectionPool->Queue(std::make_shared<::Query>(Type, Format, Parameters), std::move(Callback), std::move(Result));
	}

private:

	friend class Singleton<MySQL>;

	MySQL();
	~MySQL() = default;
	
	std::unique_ptr<ConnectionPool> m_connectionPool;
};
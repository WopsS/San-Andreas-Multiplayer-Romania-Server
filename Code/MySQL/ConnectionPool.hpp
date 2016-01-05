#pragma once

class ConnectionPool
{
public:

	ConnectionPool(uint32_t Size);
	~ConnectionPool();

	void ProcessCallbacks();

	void Queue(std::shared_ptr<Query> Query, std::function<void()> Callback, std::shared_ptr<MySQLResult> Result);

private:

	struct ConnectionNode
	{
		std::shared_ptr<Connection> Connection;
		std::shared_ptr<ConnectionNode> Next;
	};

	void DestroyNodes(std::shared_ptr<ConnectionNode> StartNode);

	std::shared_ptr<ConnectionNode> m_logNode;
	std::shared_ptr<ConnectionNode> m_normalNode;

};
#pragma once

class CConnectionPool
{
public:

	CConnectionPool(uint32_t Size);
	~CConnectionPool();

	void ProcessCallbacks();

	void Queue(std::shared_ptr<CQuery> Query, std::function<void()> Callback, std::shared_ptr<CResult> Result);

private:

	struct ConnectionNode
	{
		std::shared_ptr<CConnection> Connection;
		std::shared_ptr<ConnectionNode> Next;
	};

	void DestroyNodes(std::shared_ptr<ConnectionNode> StartNode);

	std::shared_ptr<ConnectionNode> m_logNode;
	std::shared_ptr<ConnectionNode> m_normalNode;

};
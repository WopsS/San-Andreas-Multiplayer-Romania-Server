#include <MySQL/ConnectionPool.hpp>

ConnectionPool::ConnectionPool(uint32_t Size)
{
	Logger::GetInstance()->Log(LogLevel::kDebug, "ConnectionPool::ConnectionPool(this={}, size={})", static_cast<const void*>(this), Size);

	// Create connections for player / business / houses / etc. queies.
	m_normalNode = std::make_shared<ConnectionNode>();
	auto Node = m_normalNode;

	for (uint32_t i = 1; i <= Size; i++)
	{
		Node->Connection = std::make_shared<Connection>("sa-mp.ro", "sampro_server", "sampro_server", "9VXKr3ZrmVhEf3aj");
		Node->Next = (i + 1) > Size ? m_normalNode : std::make_shared<ConnectionNode>();

		Node = Node->Next;
	}

	// Create connections for logs queries.
	m_logNode = std::make_shared<ConnectionNode>();
	Node = m_logNode;

	for (uint32_t i = 1; i <= Size; i++)
	{
		Node->Connection = std::make_shared<Connection>("sa-mp.ro", "sampro_server", "sampro_server", "9VXKr3ZrmVhEf3aj");
		Node->Next = (i + 1) > Size ? m_logNode : std::make_shared<ConnectionNode>();

		Node = Node->Next;
	}

	Logger::GetInstance()->Log(LogLevel::kDebug, "ConnectionPool::ConnectionPool - new connections = {} ", Size * 2);
}

ConnectionPool::~ConnectionPool()
{
	Logger::GetInstance()->Log(LogLevel::kDebug, "ConnectionPool::~ConnectionPool(this={})", static_cast<const void*>(this));

	DestroyNodes(std::move(m_normalNode));
	DestroyNodes(std::move(m_logNode));
}

void ConnectionPool::ProcessCallbacks()
{
	auto Node = m_normalNode;

	do
	{
		Node->Connection->ProcessCallbacks();
		Node = Node->Next;
	} while (Node.get() != m_normalNode.get());
}

void ConnectionPool::Queue(std::shared_ptr<Query> Query, std::function<void()> Callback, std::shared_ptr<MySQLResult> Result)
{
	if (Query->GetType() == QueryType::kLog)
	{
		m_logNode->Connection->Queue(std::move(Query), std::move(Callback), std::move(Result));
		m_logNode = m_logNode->Next;
	}
	else
	{
		m_normalNode->Connection->Queue(std::move(Query), std::move(Callback), std::move(Result));
		m_normalNode = m_normalNode->Next;
	}
}

void ConnectionPool::DestroyNodes(std::shared_ptr<ConnectionNode> StartNode)
{
	// Current node will be the last deleted because we have a circular list.

	auto Node = std::move(StartNode);
	
	do
	{
		auto OldNode = std::move(Node);
		Node = std::move(OldNode->Next);
	} while (Node.get() != m_normalNode.get());
	
	Node.reset();
}

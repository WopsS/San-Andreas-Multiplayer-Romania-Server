#pragma once

class Server : public Singleton<Server>
{
public:

	void Initialize();

private:

	friend class Singleton<Server>;

	Server() = default;
	~Server() = default;

	void InitializeBusinesses(std::shared_ptr<MySQLResult> Result);

	void InitializeFactions(std::shared_ptr<MySQLResult> Result);

	void InitializeHouses(std::shared_ptr<MySQLResult> Result);

	void InitializeVehicles(std::shared_ptr<MySQLResult> Result);
};
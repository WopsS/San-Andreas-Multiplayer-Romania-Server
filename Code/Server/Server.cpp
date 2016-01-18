#include <stdafx.hpp>
#include <Server/Server.hpp>

#include <Business/Business.hpp>
#include <Faction/Faction.hpp>
#include <House/House.hpp>
#include <Vehicle/Vehicle.hpp>

void Server::Initialize()
{
	//MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `businesses`", {}, &Server::InitializeBusinesses, this);
	MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `factions`", {}, &Server::InitializeFactions, this);
	//MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `houses`", {}, &Server::InitializeHouses, this);
	//MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `faction_vehicles`", {}, &Server::InitializeVehicles, this);
}

void Server::InitializeBusinesses(std::shared_ptr<MySQLResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		Business::Add(i + 1, Result->GetRowResult(i));
	}

	sampgdk::logprintf(fmt::format("Server::Initialize: {} businesses loaded.", Result->GetRowCount()).c_str());
}

void Server::InitializeFactions(std::shared_ptr<MySQLResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		Faction::Add(i + 1, Result->GetRowResult(i));
	}

	sampgdk::logprintf(fmt::format("Server::Initialize: {} factions loaded.", Result->GetRowCount()).c_str());
}

void Server::InitializeHouses(std::shared_ptr<MySQLResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		House::Add(i + 1, Result->GetRowResult(i));
	}

	sampgdk::logprintf(fmt::format("Server::Initialize: {} houses loaded.", Result->GetRowCount()).c_str());
}

void Server::InitializeVehicles(std::shared_ptr<MySQLResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		Vehicle::Add(i + 1, Result->GetRowResult(i));
	}

	sampgdk::logprintf(fmt::format("Server::Initialize: {} vehicles loaded.", Result->GetRowCount()).c_str());
}

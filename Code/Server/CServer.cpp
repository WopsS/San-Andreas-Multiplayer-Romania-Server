#include <Server/CServer.hpp>

#include <Business/CBusiness.hpp>
#include <Faction/CFaction.hpp>
#include <House/CHouse.hpp>
#include <Vehicle/CVehicle.hpp>

void CServer::Initialize()
{
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `businesses`", {}, &CServer::InitializeBusinesses, this);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `factions`", {}, &CServer::InitializeFactions, this);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `houses`", {}, &CServer::InitializeHouses, this);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `faction_vehicles`", {}, &CServer::InitializeVehicles, this);
}

void CServer::InitializeBusinesses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CBusiness::Add(i + 1, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} businesses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeFactions(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CFaction::Add(i + 1, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} factions loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeHouses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CHouse::Add(i + 1, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} houses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeVehicles(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CVehicle::Add(i + 1, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} vehicles loaded.", Result->GetRowCount()).c_str());
}

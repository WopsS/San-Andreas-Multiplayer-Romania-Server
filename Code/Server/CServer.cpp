#include <Server/CServer.hpp>

CServer::CServer()
{
}

CServer::~CServer()
{
}

void CServer::Initialize()
{
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `businesses`", {}, &CServer::InitializeBusinesses, this);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `houses`", {}, &CServer::InitializeHouses, this);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `faction_vehicles`", {}, &CServer::InitializeVehicles, this);
}

void CServer::InitializeBusinesses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CBusiness::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} businesses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeHouses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CHouse::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} houses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeVehicles(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CVehicle::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} vehicles loaded.", Result->GetRowCount()).c_str());
}

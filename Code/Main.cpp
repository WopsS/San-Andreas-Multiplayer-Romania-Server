#include <stdafx.hpp>

#include <mysql.h>
#include <Log/CLog.hpp>
#include <Dialog/Enums.hpp>
#include <MySQL/CMySQL.hpp>
#include <Player/CPlayer.hpp>
#include <Server/CServer.hpp>
#include <Utilities/Time.hpp>

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	sampgdk::SetGameModeText(SERVER_VERSION);
	sampgdk::ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	sampgdk::EnableStuntBonusForAll(false);
	sampgdk::UsePlayerPedAnims();
	sampgdk::DisableInteriorEnterExits();
	sampgdk::ManualVehicleEngineAndLights();
	sampgdk::SetNameTagDrawDistance(40.0);
	sampgdk::SetWorldTime(std::stoi(Time::GetHour()));

	// Initialize server things.
	CServer::GetInstance()->Initialize();

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int PlayerID)
{
	CPlayer::Add(static_cast<uint16_t>(PlayerID));

	auto Player = CPlayer::Get(PlayerID);

	if (Player == nullptr)
	{
		return false;
	}

	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `Name` = ':name' LIMIT 1", { CMySQL::GetInstance()->MakeParameter("name", Player->GetName()) }, Player, &CPlayer::OnConnect);

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int PlayerID, int Reason)
{
	auto Player = CPlayer::Get(PlayerID);

	if (Player == nullptr)
	{
		return false;
	}

	Player->OnDisconnect(static_cast<DisconnectReason>(Reason));
	CPlayer::Remove(static_cast<uint16_t>(PlayerID));

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int PlayerID, int ClassID)
{
	auto Player = CPlayer::Get(PlayerID);

	if (Player != nullptr)
	{
		// Set spawn info to prevent a 'temporary' ban for player if he is spawned at 0.0 coords.
		sampgdk::SetSpawnInfo(PlayerID, NO_TEAM, 250, 1743.0f, -1862.0f, 13.6f, 0.0f, 0, 0, 0, 0, 0, 0);
		Player->ToggleSpectating(true);
	}

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int PlayerID, const char* CMDText)
{
	auto Player = CPlayer::Get(PlayerID);

	if (Player != nullptr)
	{
		return Player->OnCommand(std::string(CMDText));
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int PlayerID, int DialogID, int Response, int ListItem, const char* InputText)
{
	auto Player = CPlayer::Get(PlayerID);

	if (Player != nullptr)
	{
		return Player->OnDialogResponse(static_cast<::DialogID>(DialogID), static_cast<DialogResponse>(Response), static_cast<uint32_t>(ListItem), std::string(InputText));
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int PlayerID)
{
	auto Player = CPlayer::Get(PlayerID);

	if (Player != nullptr)
	{
		Player->OnSpawn();
	}

	return true;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** appData)
{
	if (mysql_library_init(0, nullptr, nullptr))
	{
		sampgdk::logprintf("  SAMPRomania: Could not initialize MySQL library.");
	}

	sampgdk::logprintf("  SAMPRomania: %s successfully loaded.", SERVER_VERSION);
	return sampgdk::Load(appData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	sampgdk::logprintf("  SAMPRomania: Unloading plugin...", SERVER_VERSION);

	CMySQL::DestroyInstance();
	CLog::DestroyInstance();

	mysql_library_end();

	sampgdk::logprintf("  SAMPRomania: Plugin unloaded.", SERVER_VERSION);
	sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
	CMySQL::GetInstance()->ProcessCallbacks();
}
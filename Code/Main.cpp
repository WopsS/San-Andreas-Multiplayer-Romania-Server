#include <stdafx.hpp>

#include <mysql.h>
#include <Log/CLog.hpp>
#include <MySQL/CMySQL.hpp>
#include <Player/CPlayer.hpp>

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	sampgdk::SetGameModeText(SERVER_VERSION);
	sampgdk::ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	sampgdk::EnableStuntBonusForAll(false);
	sampgdk::UsePlayerPedAnims();
	sampgdk::DisableInteriorEnterExits();
	sampgdk::ManualVehicleEngineAndLights();
	sampgdk::SetNameTagDrawDistance(40.0);
	sampgdk::SetWorldTime(12);

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int PlayerID)
{
	CPlayer::Add(static_cast<uint16_t>(PlayerID));

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int PlayerID, int Reason)
{
	CPlayer::Remove(static_cast<uint16_t>(PlayerID));

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int PlayerID, int ClassID)
{
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int PlayerID, const char* CMDText)
{
	auto pPlayer = CPlayer::Get(PlayerID);

	if (pPlayer == nullptr)
	{
		return false;
	}

	return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** appData)
{
	if (mysql_library_init(0, NULL, NULL)) 
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
}
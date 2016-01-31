#include <stdafx.hpp>
#include <Commands/Commands.hpp>
#include <Dialogs/Dialogs.hpp>
#include <Key/Keys.hpp>
#include <Player/Player.hpp>
#include <Server/Server.hpp>

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
	Server::GetInstance()->Initialize();

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int PlayerID)
{
	Player::Add(static_cast<uint16_t>(PlayerID), static_cast<uint16_t>(PlayerID));

	auto Player = Player::Get(PlayerID);

	if (Player == nullptr)
	{
		return false;
	}

	MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `Name` = ':name' LIMIT 1", { MySQL::GetInstance()->MakeParameter("name", Player->GetName()) }, &Player::OnConnect, Player);

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int PlayerID, int Reason)
{
	auto Player = Player::Get(PlayerID);

	if (Player == nullptr)
	{
		return false;
	}

	Player->OnDisconnect(static_cast<DisconnectReason>(Reason));
	Player::Remove(static_cast<uint16_t>(PlayerID));

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int PlayerID, int ClassID)
{
	auto Player = Player::Get(PlayerID);

	if (Player != nullptr)
	{
		sampgdk::SetPlayerCameraPos(PlayerID, 1500.7156f, -1778.1880f, 80.3080f);
		sampgdk::SetPlayerCameraLookAt(PlayerID, 1500.7156f, -1778.1880f, 80.3080f);

		// Set spawn info to prevent a 'temporary' ban for player if he is spawned at 0.0 coords.
		sampgdk::SetSpawnInfo(PlayerID, NO_TEAM, 250, 1743.0f, -1862.0f, 13.6f, 0.0f, 0, 0, 0, 0, 0, 0);
		Player->ToggleSpectating(true);
	}

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int PlayerID, const char* CMDText)
{
	auto Player = Player::Get(PlayerID);

	if (Player != nullptr)
	{
		return Commands::GetInstance()->Execute(Player, std::string(CMDText));
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int PlayerID, int DialogID, int Response, int ListItem, const char* InputText)
{
	auto Player = Player::Get(PlayerID);

	if (Player != nullptr)
	{
		return Dialogs::GetInstance()->Execute(Player, static_cast<::DialogID>(DialogID), static_cast<DialogResponse>(Response), static_cast<uint32_t>(ListItem), std::string(InputText));
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int PlayerID)
{
	auto Player = Player::Get(PlayerID);

	if (Player != nullptr)
	{
		Player->OnSpawn();
	}

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerKeyStateChange(int PlayerID, int NewKeys, int OldKeys)
{
	auto Player = Player::Get(PlayerID);

	if (Player != nullptr)
	{
		Keys::GetInstance()->OnPress(Player, NewKeys, OldKeys);
	}

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPublicCall(AMX *amx, const char *name, cell *params, cell *retval) 
{
	auto Name = std::string(name);

	if (Name.compare("OnPlayerEditDynamicObject") == 0)
	{
		auto Player = Player::Get(static_cast<uint16_t>(params[1]));

		if (Player != nullptr)
		{
			Player->OnObjectEdit(params[2], static_cast<ObjectEditionResponse>(params[3]), Point3D<float>(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])), Point3D<float>(amx_ctof(params[7]), amx_ctof(params[8]), amx_ctof(params[9])));
		}
	}
	else if (Name.compare("OnPlayerPickUpDynamicPickup") == 0)
	{
		auto Player = Player::Get(static_cast<uint16_t>(params[1]));

		if (Player != nullptr)
		{
			Player->OnPickUp(params[2]);
		}
	}
	else if (Name.compare("OnPlayerSelectDynamicObject") == 0)
	{
		auto Player = Player::Get(static_cast<uint16_t>(params[1]));

		if (Player != nullptr)
		{
			Player->OnObjectSelect(params[2], params[3], Point3D<float>(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
		}
	}

	/* Unimplemented:
			* forward OnDynamicObjectMoved(STREAMER_TAG_OBJECT objectid);
			* forward OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z);
			* forward OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid);
			* forward OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP checkpointid);
			* forward OnPlayerEnterDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid);
			* forward OnPlayerLeaveDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid);
			* forward OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid);
			* forward OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA areaid);
			* forward Streamer_OnPluginError(error[]);
	*/

	return true;
}

PLUGIN_EXPORT uint32_t PLUGIN_CALL Supports()
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

	MySQL::DestroyInstance();
	Logger::DestroyInstance();

	mysql_library_end();

	sampgdk::logprintf("  SAMPRomania: Plugin unloaded.", SERVER_VERSION);
	sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
	MySQL::GetInstance()->ProcessCallbacks();
}
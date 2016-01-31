#include <stdafx.hpp>

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
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
	mysql_library_end();

	sampgdk::logprintf("  SAMPRomania: Plugin unloaded.", SERVER_VERSION);
	sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
}
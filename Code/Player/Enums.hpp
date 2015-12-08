#pragma once

#include <cstdint>

// See <a href="http://wiki.sa-mp.com/wiki/OnPlayerDisconnect">OnPlayerDisconnect on SA-MP Wiki</a>.
enum class DisconnectReason : uint16_t
{
	kTimeout = 0, // The player's connection was lost. Either their game crashed or their network had a fault. 
	kQuit, // The player purposefully quit, either using the /quit (/q) command or via the pause menu.
	kKick // The player was kicked or banned by the server. 
};

enum class PlayerSex : uint16_t
{
	kMale = 1,
	kFemale
};

enum class PlayerData : uint16_t
{
	// Variables from MySQL.

	kMySQLID = 0,
	kName,
	kPassword,
	kSalt,
	kEmail,
	kPin,
	kSex,
	kAdminLevel,
	kCash,
	kAccount, // Money in the bank.

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.

			   // Variables used temporary in game.
	kGameID,
	kAuthenticated,
	kSpectating
};
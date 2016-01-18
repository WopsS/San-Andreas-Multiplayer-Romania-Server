#pragma once

enum class AdminLevel : uint8_t
{
	kLevelZero = 0,
	kLevelOne,
	kLevelTwo,
	kLevelThree,
	kLevelFour,
	kLevelFive,
	kLevelSix
};

// See <a href="http://wiki.sa-mp.com/wiki/OnPlayerDisconnect">OnPlayerDisconnect on SA-MP Wiki</a>.
enum class DisconnectReason : uint8_t
{
	kTimeout = 0, // The player's connection was lost. Either their game crashed or their network had a fault. 
	kQuit, // The player purposefully quit, either using the /quit (/q) command or via the pause menu.
	kKick // The player was kicked or banned by the server. 
};

enum class Interior : uint8_t
{
	kWorld = 0,
	kHouse,
	kBusiness
};

enum class PlayerSex : uint8_t
{
	kMale = 1,
	kFemale
};

enum class PlayerData : uint8_t
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
	kMoney,

	// Variables used temporary in game.

	kGameID,
	kAuthenticated,
	kInterior,
	kInteriorID,
	kSpectating
};
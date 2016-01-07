#pragma once

enum class AdminLevel : unsigned char
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
enum class DisconnectReason : unsigned char
{
	kTimeout = 0, // The player's connection was lost. Either their game crashed or their network had a fault. 
	kQuit, // The player purposefully quit, either using the /quit (/q) command or via the pause menu.
	kKick // The player was kicked or banned by the server. 
};

enum class Interior : unsigned char
{
	kWorld = 0,
	kHouse,
	kBusiness
};

enum class PlayerSex : unsigned char
{
	kMale = 1,
	kFemale
};

enum class PlayerData : unsigned char
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
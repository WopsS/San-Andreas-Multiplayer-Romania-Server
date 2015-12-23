#pragma once

#include <cstdint>

enum class BusinessData : uint8_t
{
	kID = 0,
	kOwnerID,
	kName,
	kType,
	kEntrance,
	kExit = kEntrance + 3,
	kInterior = kExit + 3,
	kVirtualWorld,
	kLocked,
	kPrice,
	kLevel,
	kPayout,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.

	kMapIconID,
	kPickupID,
	kTextLabelID
};

enum class BusinessType : uint8_t
{
	kBank = 1,
	kGunShop
};
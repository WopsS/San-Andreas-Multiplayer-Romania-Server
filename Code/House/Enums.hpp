#pragma once

#include <cstdint>

enum class HouseData : uint16_t
{
	kID = 0,
	kOwnerID,
	kEntrance,
	kExit = kEntrance + 3,
	kInterior = kExit + 3,
	kVirtualWorld,
	kLocked,
	kPrice,
	kLevel,
	kRentPrice,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.

	kMapIconID,
	kPickupID,
	kTextLabelID
};
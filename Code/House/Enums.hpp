#pragma once

#include <cstdint>

enum class HouseData : uint16_t
{
	kID = 0,
	kOwnerID,
	kEntrance,
	kExit = kEntrance + 3,
	kPrice = kExit + 3,
	kInterior,
	kVirtualWorld,
	kLock,
	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.
};
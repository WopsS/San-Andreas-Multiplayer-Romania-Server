#pragma once

enum class HouseData : uint8_t
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

	kMapIconID,
	kPickupID,
	kTextLabelID
};
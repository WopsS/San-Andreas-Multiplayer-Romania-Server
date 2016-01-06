#pragma once

enum class HouseData : unsigned char
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
#pragma once

enum class BusinessData : unsigned char
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

	kMapIconID,
	kPickupID,
	kTextLabelID
};

enum class BusinessType : unsigned char
{
	kBank = 1,
	kGunShop
};
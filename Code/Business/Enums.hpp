#pragma once

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

	kMapIconID,
	kPickupID,
	kTextLabelID
};

enum class BusinessType : uint8_t
{
	kBank = 1,
	kGunShop
};
#pragma once

#include <cstdint>

enum class BusinessData : uint16_t
{
	kID = 0,
	kOwnerID,
	kEnterance,
	kExit = kEnterance + 3,
	kPrice = kExit + 3,
	kInterior,
	kVirtualWorld,
	kLock,
	kType,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.

	kIconID,
};

enum class BusinessType : uint16_t
{
	kBank = 1
};
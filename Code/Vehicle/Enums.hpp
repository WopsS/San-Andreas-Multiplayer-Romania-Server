#pragma once

#include <cstdint>

enum class VehicleData : uint16_t
{
	kID = 0,
	kOwnerID,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.
};
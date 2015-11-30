#pragma once

#include <cstdint>

enum class VehicleData : uint16_t
{
	kID = 0,
	kOwnerID,
	kModel,
	kPosition,
	kRotation = kPosition + 3, // kPosition + 3, de ce? Pentru ca avem 3 axe in spatiul 3D. X, Y, Z. Si o sa pastram pozitia intr-o clasa de tip-ul Point3D
	kColor1,
	kColor2,
	kRespawnTime,
	kSiren,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.

	kGameID
};

enum class VehicleParameters : uint16_t
{
	kEngine,
	kLights,
	kAlarm,
	kDoors,
	kBonnet,
	kBoot,
	kObjective
};
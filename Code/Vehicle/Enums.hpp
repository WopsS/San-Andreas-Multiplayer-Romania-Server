#pragma once

enum class VehicleData : unsigned char
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

	kGameID
};

enum class VehicleParameters : unsigned char
{
	kEngine,
	kLights,
	kAlarm,
	kDoors,
	kBonnet,
	kBoot,
	kObjective
};
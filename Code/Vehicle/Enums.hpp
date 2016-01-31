#pragma once

enum class VehicleData : uint8_t
{
	kID = 0,
	kOwnerID,
	kModel,
	kPosition,
	kRotation = kPosition + 3,
	kColor1,
	kColor2,
	kRespawnTime,
	kSiren,

	kGameID
};

enum class VehicleParameters : uint8_t
{
	kEngine,
	kLights,
	kAlarm,
	kDoors,
	kBonnet,
	kBoot,
	kObjective
};
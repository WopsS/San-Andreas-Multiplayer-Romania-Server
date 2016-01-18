#pragma once

#ifndef STREAMER_3D_TEXT_LABEL_SD
#define STREAMER_3D_TEXT_LABEL_SD 200.0f
#endif

namespace TextLabel
{
	uint32_t Create(const std::string& Text, int32_t Color, Point3D<float> Position, float DrawDistance = 5.0f, uint16_t AttachedPlayer = INVALID_PLAYER_ID, uint16_t AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int32_t VirtualWorld = -1, int32_t Interior = -1, uint16_t PlayerID = INVALID_PLAYER_ID, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	uint32_t Create(const std::string& Text, int32_t Color, float X, float Y, float Z, float DrawDistance = 5.0f, uint16_t AttachedPlayer = INVALID_PLAYER_ID, uint16_t AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int32_t VirtualWorld = -1, int32_t Interior = -1, uint16_t PlayerID = INVALID_PLAYER_ID, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	const bool Destroy(uint32_t ID);

	const bool IsValid(int32_t ID);

	const std::string GetText(int32_t ID);

	const bool UpdateText(int32_t ID, int32_t Color, const std::string& Text);

	/* Unimplemented:
		* native STREAMER_TAG_3D_TEXT_LABEL CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
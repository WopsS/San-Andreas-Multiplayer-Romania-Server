#pragma once

#ifndef STREAMER_3D_TEXT_LABEL_SD
#define STREAMER_3D_TEXT_LABEL_SD 200.0f
#endif

namespace TextLabel
{
	unsigned int Create(const std::string& Text, int Color, Point3D<float> Position, float DrawDistance = 5.0f, unsigned short AttachedPlayer = INVALID_PLAYER_ID, unsigned short AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int VirtualWorld = -1, int Interior = -1, unsigned short PlayerID = INVALID_PLAYER_ID, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	unsigned int Create(const std::string& Text, int Color, float X, float Y, float Z, float DrawDistance = 5.0f, unsigned short AttachedPlayer = INVALID_PLAYER_ID, unsigned short AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int VirtualWorld = -1, int Interior = -1, unsigned short PlayerID = INVALID_PLAYER_ID, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	const bool Destroy(unsigned int ID);

	const bool IsValid(int ID);

	const std::string GetText(int ID);

	const bool UpdateText(int ID, int Color, const std::string& Text);

	/* Unimplemented:
		* native STREAMER_TAG_3D_TEXT_LABEL CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <stdafx.hpp>
#include <Base/CPoint.hpp>
#include <Player/CPlayer.hpp>

#ifndef STREAMER_3D_TEXT_LABEL_SD
#define STREAMER_3D_TEXT_LABEL_SD 200.0f
#endif

namespace TextLabel
{
	uint32_t Create(const std::string& Text, int Color, Point3D<float> Position, float DrawDistance = 5.0f, uint16_t AttachedPlayer = INVALID_PLAYER_ID, uint16_t AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int VirtualWorld = -1, int Interior = -1, std::shared_ptr<CPlayer> Player = nullptr, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	uint32_t Create(const std::string& Text, int Color, float X, float Y, float Z, float DrawDistance = 5.0f, uint16_t AttachedPlayer = INVALID_PLAYER_ID, uint16_t AttachedVehicle = INVALID_VEHICLE_ID, bool TestLOS = false, int VirtualWorld = -1, int Interior = -1, std::shared_ptr<CPlayer> Player = nullptr, float StreamDistance = STREAMER_3D_TEXT_LABEL_SD);

	const bool Destroy(uint32_t ID);

	const bool IsValid(int ID);

	const std::string GetText(int ID);

	const bool UpdateText(int ID, int Color, const std::string& Text);

	/* Unimplemented:
		* native STREAMER_TAG_3D_TEXT_LABEL CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
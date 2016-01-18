#pragma once

#ifndef STREAMER_MAP_ICON_SD
#define STREAMER_MAP_ICON_SD 200.0f
#endif

enum class MapIconStlye : uint8_t
{
	kLocal = 0, // Display in the player's local area.
	kGlobal, // Display always.
	kLocalCheckpoint, // Display in the player's local area and has a checkpoint marker.
	kGlobalCheckpoint // Display always and has a checkpoint marker.
};

namespace MapIcon
{
	const uint32_t Create(Point3D<float> Position, uint16_t Type, int32_t Color = Color::kBlack, int32_t VirtualWorld = -1, int32_t Interior = -1, int32_t PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const uint32_t Create(float X, float Y, float Z, uint16_t Type, int32_t Color = Color::kBlack, int32_t VirtualWorld = -1, int32_t Interior = -1, int32_t PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const bool Destroy(uint32_t ID);

	const bool IsValid(uint32_t ID);

	/* Unimplemented:
		* native STREAMER_TAG_MAP_ICON CreateDynamiMapIconEx(Float:x, Float:y, Float:z, type, color, style = MAPICON_LOCAL, Float:streamdistance = STREAMER_MAP_ICON_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
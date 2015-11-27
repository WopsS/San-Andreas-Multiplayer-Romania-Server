#pragma once

#include <cstdint>

#include <stdafx.hpp>
#include <Base/CPoint.hpp>

#ifndef STREAMER_MAP_ICON_SD
#define STREAMER_MAP_ICON_SD 200.0f
#endif

enum class MapIconStlye : uint16_t
{
	kLocal = 0, // Display in the player's local area.
	kGlobal, // Display always.
	kLocalCheckpoint, // Display in the player's local area and has a checkpoint marker.
	kGlobalCheckpoint // Display always and has a checkpoint marker.
};

namespace MapIcon
{
	const uint32_t Create(Point3D<float> Position, uint16_t Type, int Color = 0x000000FF, int VirtualWorld = -1, int Interior = -1, int PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const uint32_t Create(float X, float Y, float Z, uint16_t Type, int Color = 0x000000FF, int VirtualWorld = -1, int Interior = -1, int PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const bool Destroy(uint32_t ID);

	const bool IsValid(uint32_t ID);
}
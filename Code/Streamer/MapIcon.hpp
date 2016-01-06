#pragma once

#ifndef STREAMER_MAP_ICON_SD
#define STREAMER_MAP_ICON_SD 200.0f
#endif

enum class MapIconStlye : unsigned char
{
	kLocal = 0, // Display in the player's local area.
	kGlobal, // Display always.
	kLocalCheckpoint, // Display in the player's local area and has a checkpoint marker.
	kGlobalCheckpoint // Display always and has a checkpoint marker.
};

namespace MapIcon
{
	const unsigned int Create(Point3D<float> Position, unsigned short Type, int Color = Color::kBlack, int VirtualWorld = -1, int Interior = -1, int PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const unsigned int Create(float X, float Y, float Z, unsigned short Type, int Color = Color::kBlack, int VirtualWorld = -1, int Interior = -1, int PlayerID = -1, float StreamDistance = STREAMER_MAP_ICON_SD, MapIconStlye Style = MapIconStlye::kLocal);

	const bool Destroy(unsigned int ID);

	const bool IsValid(unsigned int ID);

	/* Unimplemented:
		* native STREAMER_TAG_MAP_ICON CreateDynamiMapIconEx(Float:x, Float:y, Float:z, type, color, style = MAPICON_LOCAL, Float:streamdistance = STREAMER_MAP_ICON_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
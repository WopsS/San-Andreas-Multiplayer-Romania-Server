#pragma once

#ifndef STREAMER_PICKUP_SD
#define STREAMER_PICKUP_SD 200.0f
#endif

namespace Pickup
{
	int Create(int ModelID, int Type, const Point3D<float>& Position, int VirtualWorld = -1, int Interior = -1, int PlayerID = -1, float StreamDistance = STREAMER_PICKUP_SD);

	const bool Destroy(int ID);

	const bool IsValid(int ID);

	/* Unimplemented:
		* native STREAMER_TAG_PICKUP CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = STREAMER_PICKUP_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
#pragma once

#ifndef STREAMER_PICKUP_SD
#define STREAMER_PICKUP_SD 200.0f
#endif

namespace Pickup
{
	int Create(int32_t ModelID, int32_t Type, const Point3D<float>& Position, int32_t VirtualWorld = -1, int32_t Interior = -1, int32_t PlayerID = -1, float StreamDistance = STREAMER_PICKUP_SD);

	const bool Destroy(int32_t ID);

	const bool IsValid(int32_t ID);

	/* Unimplemented:
		* native STREAMER_TAG_PICKUP CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = STREAMER_PICKUP_SD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
	*/
}
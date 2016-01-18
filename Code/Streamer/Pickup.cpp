#include <Streamer/Pickup.hpp>

int32_t Pickup::Create(int32_t ModelID, int32_t Type, const Point3D<float>& Position, int32_t VirtualWorld, int32_t Interior, int32_t PlayerID, float StreamDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamicPickup");
	return static_cast<int32_t>(sampgdk::InvokeNative(Native, "iifffiiif", ModelID, Type, Position.X, Position.Y, Position.Z, VirtualWorld, Interior, PlayerID, StreamDistance));
}

const bool Pickup::Destroy(int32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamicPickup");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Pickup::IsValid(int32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamicPickup");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

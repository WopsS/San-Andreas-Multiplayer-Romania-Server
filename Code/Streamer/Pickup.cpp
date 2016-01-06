#include <Streamer/Pickup.hpp>

int Pickup::Create(int ModelID, int Type, const Point3D<float>& Position, int VirtualWorld, int Interior, int PlayerID, float StreamDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamicPickup");
	return static_cast<int>(sampgdk::InvokeNative(Native, "iifffiiif", ModelID, Type, Position.X, Position.Y, Position.Z, VirtualWorld, Interior, PlayerID, StreamDistance));
}

const bool Pickup::Destroy(int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamicPickup");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Pickup::IsValid(int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamicPickup");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

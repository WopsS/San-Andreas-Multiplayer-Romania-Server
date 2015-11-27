#include <Streamer/MapIcon.hpp>

const uint32_t MapIcon::Create(Point3D<float> Position, uint16_t Type, int Color, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, MapIconStlye Style)
{
	return Create(Position.X, Position.Y, Position.Z, Type, Color, VirtualWorld, Interior, PlayerID, StreamDistance, Style);
}

const uint32_t MapIcon::Create(float X, float Y, float Z, uint16_t Type, int Color, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, MapIconStlye Style)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamicMapIcon");
	return static_cast<uint32_t>(sampgdk::InvokeNative(Native, "fffiiiiifi", X, Y, Z, Type, Color, VirtualWorld, Interior, PlayerID, StreamDistance, static_cast<int>(Style)));
}

const bool MapIcon::Destroy(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamicMapIcon");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool MapIcon::IsValid(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamicMapIcon");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

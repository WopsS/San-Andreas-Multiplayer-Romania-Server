#include <Streamer/MapIcon.hpp>

const unsigned int MapIcon::Create(Point3D<float> Position, unsigned short Type, int Color, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, MapIconStlye Style)
{
	return Create(Position.X, Position.Y, Position.Z, Type, Color, VirtualWorld, Interior, PlayerID, StreamDistance, Style);
}

const unsigned int MapIcon::Create(float X, float Y, float Z, unsigned short Type, int Color, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, MapIconStlye Style)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamiMapIcon");
	return static_cast<unsigned int>(sampgdk::InvokeNative(Native, "fffiiiiifi", X, Y, Z, Type, Color, VirtualWorld, Interior, PlayerID, StreamDistance, static_cast<int>(Style)));
}

const bool MapIcon::Destroy(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamiMapIcon");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool MapIcon::IsValid(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamiMapIcon");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

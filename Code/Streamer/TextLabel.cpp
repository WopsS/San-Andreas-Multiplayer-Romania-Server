#include <Streamer/TextLabel.hpp>
#include <Player/Player.hpp>

unsigned int TextLabel::Create(const std::string& Text, int Color, Point3D<float> Position, float DrawDistance, unsigned short AttachedPlayer, unsigned short AttachedVehicle, bool TestLOS, int VirtualWorld, int Interior, unsigned short PlayerID, float StreamDistance)
{
	return Create(Text, Color, Position.X, Position.Y, Position.Z, DrawDistance, AttachedPlayer, AttachedVehicle, TestLOS, VirtualWorld, Interior, PlayerID, StreamDistance);
}

unsigned int TextLabel::Create(const std::string& Text, int Color, float X, float Y, float Z, float DrawDistance, unsigned short AttachedPlayer, unsigned short AttachedVehicle, bool TestLOS, int VirtualWorld, int Interior, unsigned short PlayerID, float StreamDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "siffffiibiiif", Text.c_str(), Color, X, Y, Z, DrawDistance, AttachedPlayer, AttachedVehicle, TestLOS, VirtualWorld, Interior, PlayerID == INVALID_PLAYER_ID ? -1 : Player::Get(PlayerID)->GetGameID(), StreamDistance);
}

const bool TextLabel::Destroy(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool TextLabel::IsValid(int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const std::string TextLabel::GetText(int ID)
{
	char Text[2048];

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamic3DTextLabelText");
	sampgdk::InvokeNative(Native, "iS[2048]i", ID, &Text, 2048);

	std::stringstream Result;
	Result << Text;

	return Result.str();
}

const bool TextLabel::UpdateText(int ID, int Color, const std::string& Text)
{
	static AMX_NATIVE Native = sampgdk::FindNative("UpdateDynamic3DTextLabelText");
	return !!sampgdk::InvokeNative(Native, "iis", ID, Color, Text.c_str());
}

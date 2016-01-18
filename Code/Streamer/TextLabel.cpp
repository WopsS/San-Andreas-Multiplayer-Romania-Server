#include <Streamer/TextLabel.hpp>
#include <Player/Player.hpp>

uint32_t TextLabel::Create(const std::string& Text, int32_t Color, Point3D<float> Position, float DrawDistance, uint16_t AttachedPlayer, uint16_t AttachedVehicle, bool TestLOS, int32_t VirtualWorld, int32_t Interior, uint16_t PlayerID, float StreamDistance)
{
	return Create(Text, Color, Position.X, Position.Y, Position.Z, DrawDistance, AttachedPlayer, AttachedVehicle, TestLOS, VirtualWorld, Interior, PlayerID, StreamDistance);
}

uint32_t TextLabel::Create(const std::string& Text, int32_t Color, float X, float Y, float Z, float DrawDistance, uint16_t AttachedPlayer, uint16_t AttachedVehicle, bool TestLOS, int32_t VirtualWorld, int32_t Interior, uint16_t PlayerID, float StreamDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "siffffiibiiif", Text.c_str(), Color, X, Y, Z, DrawDistance, AttachedPlayer, AttachedVehicle, TestLOS, VirtualWorld, Interior, PlayerID == INVALID_PLAYER_ID ? -1 : Player::Get(PlayerID)->GetGameID(), StreamDistance);
}

const bool TextLabel::Destroy(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool TextLabel::IsValid(int32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamic3DTextLabel");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const std::string TextLabel::GetText(int32_t ID)
{
	char Text[2048];

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamic3DTextLabelText");
	sampgdk::InvokeNative(Native, "iS[2048]i", ID, &Text, 2048);

	std::stringstream Result;
	Result << Text;

	return Result.str();
}

const bool TextLabel::UpdateText(int32_t ID, int32_t Color, const std::string& Text)
{
	static AMX_NATIVE Native = sampgdk::FindNative("UpdateDynamic3DTextLabelText");
	return !!sampgdk::InvokeNative(Native, "iis", ID, Color, Text.c_str());
}

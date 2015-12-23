#include <Player/CPlayer.hpp>

#include <sstream>

#include <Dialog/CDialogs.hpp>
#include <MySQL/CMySQL.hpp>
#include <Utilities/Utils.hpp>

CPlayer::CPlayer(uint16_t ID)
{
	char Name[MAX_PLAYER_NAME + 1];
	sampgdk::GetPlayerName(ID, Name, sizeof(Name));

	std::stringstream StringStream;
	StringStream << Name;

	AddData<uint16_t>(PlayerData::kGameID, ID);
	AddData<std::string>(PlayerData::kName, StringStream.str());
	AddData<bool>(PlayerData::kAuthenticated, false);
}

void CPlayer::AttachCameraToObject(int ObjectID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachCameraToDynamicObject");
	sampgdk::InvokeNative(Native, "ii", GetGameID(), ObjectID);
}

const void CPlayer::CancelEdit() const
{
	sampgdk::CancelEdit(GetData<uint16_t>(PlayerData::kGameID));
}

const bool CPlayer::EditObject(int ObjectID) const
{
	static AMX_NATIVE Native = sampgdk::FindNative("EditDynamicObject");
	return !!sampgdk::InvokeNative(Native, "ii", GetData<uint16_t>(PlayerData::kGameID), ObjectID);
}

void CPlayer::OnConnect(std::shared_ptr<CResult> Result)
{
	if (Result->GetRowCount() > 0) // Player has an account in database, store the information.
	{
		// Load user information from database.

		auto Length = static_cast<uint8_t>(PlayerData::kEndMySQL);

		for (uint8_t i = 0; i < Length; i++)
		{
			auto Index = static_cast<PlayerData>(i);
			auto Value = Result->GetRowData(Index);

			// Let's do few custom cases.
			if (Index == PlayerData::kMySQLID)
			{
				SetData<uint64_t>(PlayerData::kMySQLID, std::stoull(Value));
			}
			else if (Index == PlayerData::kSex)
			{
				SetData<PlayerSex>(PlayerData::kSex, static_cast<PlayerSex>(std::stoi(Value)));
			}
			else if (Index == PlayerData::kCash)
			{
				SetData<int>(Index, std::stoi(Value));
			}
			else if (Index == PlayerData::kAccount)
			{
				SetData<long long>(Index, std::stoll(Value));
			}
			else
			{
				auto IsFloat = Utils::IsFloat(Value);
				auto IsInteger = Utils::IsInteger(Value);
				auto IsString = IsFloat == false && IsInteger == false;

				if (IsString == true)
				{
					SetData<std::string>(Index, Value);
				}
				else if (IsInteger == true) // Check if it is a number after we check if it is as string because if the number is '0' it will return true at 'IsFloat', so probably if it is 0 it is an integer.
				{
					SetData<uint32_t>(Index, std::stoul(Value));
				}
				else if (IsFloat == true)
				{
					SetData<float>(Index, std::stof(Value));
				}
			}
		}

		// Show the dialog if user isn't authenticated.
		if (IsAuthenticated() == false)
		{
			ShowDialog(DialogID::kAuthentication, GetName());
		}
	}
	else // Player doesn't have an account in database.
	{
		ShowDialog(DialogID::kRegister, GetName());
	}
}

void CPlayer::OnDisconnect(const DisconnectReason& Reason)
{
	// TODO: Save player data.
}

void CPlayer::OnInserted(std::shared_ptr<CResult> Result)
{
	SetData<uint64_t>(PlayerData::kMySQLID, static_cast<uint64_t>(Result->GetInsertedID()));
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `ID` = ':id' LIMIT 1", { CMySQL::GetInstance()->MakeParameter("id", GetMySQLID()) }, &CPlayer::OnConnect, this);
}

void CPlayer::OnSpawn()
{
	SetPosition(1743.0f, -1862.0f, 13.6f);
}

const std::string CPlayer::GetEmail() const
{
	return GetData<std::string>(PlayerData::kEmail);
}

const uint16_t CPlayer::GetGameID() const
{
	return GetData<uint16_t>(PlayerData::kGameID);
}

const uint64_t CPlayer::GetMySQLID() const
{
	return GetData<uint64_t>(PlayerData::kMySQLID);
}

const std::shared_ptr<CVehicle> CPlayer::GetVehicle() const
{
	return CVehicle::Get(static_cast<uint16_t>(sampgdk::GetPlayerVehicleID(GetGameID())));
}

const long long CPlayer::GetAccountCash() const
{
	return GetData<long long>(PlayerData::kAccount);
}

const int CPlayer::GetCash() const
{
	return GetData<int>(PlayerData::kCash);
}

const std::string CPlayer::GetName() const
{
	return GetData<std::string>(PlayerData::kName);
}

const std::string CPlayer::GetSalt() const
{
	return GetData<std::string>(PlayerData::kSalt);
}

const PlayerSex CPlayer::GetSex() const
{
	return GetData<PlayerSex>(PlayerData::kSex);
}

void CPlayer::GiveAccountCash(long long Amount)
{
	SetData<long long>(PlayerData::kAccount, GetData<int>(PlayerData::kAccount) + Amount);
}

void CPlayer::GiveCash(int Amount)
{
	SetData<int>(PlayerData::kCash, GetData<int>(PlayerData::kCash) + Amount);
	sampgdk::GivePlayerMoney(GetGameID(), GetData<int>(PlayerData::kCash));
}

const bool CPlayer::IsAdmin() const
{
	return GetData<int>(PlayerData::kAdminLevel) >= 1;
}

const bool CPlayer::IsAuthenticated() const
{
	return GetData<bool>(PlayerData::kAuthenticated);
}

const bool CPlayer::IsInRangeOfPoint(const Point3D<float>& Position, float Range)
{
	return IsInRangeOfPoint(Position.X, Position.Y, Position.Z, Range);
}

const bool CPlayer::IsInRangeOfPoint(float X, float Y, float Z, float Range)
{
	return sampgdk::IsPlayerInRangeOfPoint(GetGameID(), X, Y, Z, Range);
}

const bool CPlayer::IsInVehicle() const
{
	return sampgdk::IsPlayerInAnyVehicle(GetGameID()) && CVehicle::Contains(sampgdk::GetPlayerVehicleID(GetGameID())) == true;
}

const bool CPlayer::IsInVehicle(uint16_t VehicleID) const
{
	return sampgdk::IsPlayerInVehicle(GetGameID(), VehicleID) && CVehicle::Contains(VehicleID) == true;
}

const bool CPlayer::Kick() const
{
	return sampgdk::Kick(GetGameID());
}

void CPlayer::SetAccountCash(long long Amount)
{
	SetData<long long>(PlayerData::kAccount, Amount);
}

void CPlayer::SetCash(int Amount)
{
	SetData<int>(PlayerData::kCash, Amount);

	sampgdk::ResetPlayerMoney(GetGameID());
	sampgdk::GivePlayerMoney(GetGameID(), Amount);
}

const bool CPlayer::SetPosition(const Point3D<float>& Position, const float Angle, const uint32_t Interior, const uint32_t VirtualWorld) const
{
	return SetPosition(Position.X, Position.Y, Position.Z, Angle, Interior, VirtualWorld);
}

const bool CPlayer::SetPosition(const float X, const float Y, const float Z, const float Angle, const uint32_t Interior, const uint32_t VirtualWorld) const
{
	auto ID = GetGameID();
	return sampgdk::SetPlayerPos(ID, X, Y, Z) && sampgdk::SetPlayerFacingAngle(ID, Angle) && sampgdk::SetPlayerInterior(ID, Interior) && sampgdk::SetPlayerVirtualWorld(ID, VirtualWorld);
}

bool CPlayer::Spawn()
{
	if (GetData<bool>(PlayerData::kSpectating) == true)
	{
		return ToggleSpectating(false);
	}

	return sampgdk::SpawnPlayer(GetGameID());
}

bool CPlayer::ToggleSpectating(const bool Toggle)
{
	SetData<bool>(PlayerData::kSpectating, Toggle);
	return sampgdk::TogglePlayerSpectating(GetGameID(), Toggle);
}

std::shared_ptr<CDialog> CPlayer::GetDialog(const DialogID& ID)  const
{
	return CDialogs::GetInstance()->Get(ID);
}
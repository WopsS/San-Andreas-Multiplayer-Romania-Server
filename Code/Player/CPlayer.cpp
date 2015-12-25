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

			switch (Index)
			{
				case PlayerData::kMySQLID:
				{
					SetData<uint64_t>(PlayerData::kMySQLID, std::stoull(Value));
					break;
				}
				case PlayerData::kSex:
				{
					SetData<PlayerSex>(PlayerData::kSex, static_cast<PlayerSex>(std::stoi(Value)));
					break;
				}
				case PlayerData::kAdminLevel:
				{
					SetData<AdminLevel>(PlayerData::kAdminLevel, static_cast<AdminLevel>(std::stoi(Value)));
					break;
				}
				default:
				{
					switch (Result->GetFieldType(Index))
					{
						case enum_field_types::MYSQL_TYPE_DOUBLE:
						{
							SetData<double>(Index, std::stod(Value));
							break;
						}
						case enum_field_types::MYSQL_TYPE_FLOAT:
						{
							SetData<float>(Index, std::stof(Value));
							break;
						}
						case enum_field_types::MYSQL_TYPE_INT24:
						case enum_field_types::MYSQL_TYPE_LONG:
						{
							SetData<int32_t>(Index, std::stoi(Value));
							break;
						}
						case enum_field_types::MYSQL_TYPE_LONGLONG:
						{
							SetData<int64_t>(Index, std::stoll(Value));
							break;
						}
						case enum_field_types::MYSQL_TYPE_SHORT:
						{
							SetData<int16_t>(Index, std::stoi(Value));
							break;
						}
						case enum_field_types::MYSQL_TYPE_TINY:
						{
							SetData<int8_t>(Index, std::stoi(Value));
							break;
						}
						default:
						{
							SetData<std::string>(Index, Value);
							break;
						}
					}

					break;
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

const AdminLevel CPlayer::GetAdminLevel() const
{
	return GetData<AdminLevel>(PlayerData::kAdminLevel);
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

const int32_t CPlayer::GetCash() const
{
	return GetData<int32_t>(PlayerData::kCash);
}

const int64_t CPlayer::GetMoney() const
{
	return GetData<int64_t>(PlayerData::kMoney);
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

void CPlayer::GiveCash(int32_t Amount)
{
	SetData<int>(PlayerData::kCash, GetData<int>(PlayerData::kCash) + Amount);
	sampgdk::GivePlayerMoney(GetGameID(), GetData<int>(PlayerData::kCash));
}

void CPlayer::GiveMoney(int64_t Amount)
{
	SetData<int64_t>(PlayerData::kMoney, GetData<int64_t>(PlayerData::kMoney) + Amount);
}

const bool CPlayer::IsAdmin() const
{
	return GetData<AdminLevel>(PlayerData::kAdminLevel) >= AdminLevel::kLevelOne;
}

const bool CPlayer::IsAuthenticated() const
{
	return GetData<bool>(PlayerData::kAuthenticated);
}

const bool CPlayer::IsInAnyFaction() const
{
	// TODO: Check if the player is in any faction.
	return false;
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

const bool CPlayer::IsLeader() const
{
	// TODO: Check if the player is leader.
	return false;
}

const bool CPlayer::IsSubleader() const
{
	// TODO: Check if the player is subleader.
	return false;
}

const bool CPlayer::Kick() const
{
	return sampgdk::Kick(GetGameID());
}

void CPlayer::SetAdminLevel(AdminLevel Level)
{
	SetData<AdminLevel>(PlayerData::kAdminLevel, Level);
}

void CPlayer::SetCash(int32_t Amount)
{
	SetData<int32_t>(PlayerData::kCash, Amount);

	sampgdk::ResetPlayerMoney(GetGameID());
	sampgdk::GivePlayerMoney(GetGameID(), Amount);
}

void CPlayer::SetMoney(int64_t Amount)
{
	SetData<int64_t>(PlayerData::kMoney, Amount);
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
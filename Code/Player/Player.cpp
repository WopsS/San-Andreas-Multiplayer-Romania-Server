#include <Player/Player.hpp>
#include <Dialog/Dialogs.hpp>

Player::Player(uint16_t ID)
{
	char Name[MAX_PLAYER_NAME + 1];
	sampgdk::GetPlayerName(ID, Name, sizeof(Name));

	std::stringstream StringStream;
	StringStream << Name;

	AddData<uint16_t>(PlayerData::kGameID, ID);
	AddData<std::string>(PlayerData::kName, StringStream.str());
	AddData<bool>(PlayerData::kAuthenticated, false);
}

void Player::AttachCameraToObject(int ObjectID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachCameraToDynamicObject");
	sampgdk::InvokeNative(Native, "ii", GetGameID(), ObjectID);
}

const bool Player::AttachObject(uint32_t ID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToPlayer");
	return !!sampgdk::InvokeNative(Native, "iiffffff", ID, GetGameID(), X, Y, Z, RotationX, RotationY, RotationZ);
}

const void Player::CancelEdit() const
{
	sampgdk::CancelEdit(GetData<uint16_t>(PlayerData::kGameID));
}

const bool Player::EditObject(int ObjectID) const
{
	static AMX_NATIVE Native = sampgdk::FindNative("EditDynamicObject");
	return !!sampgdk::InvokeNative(Native, "ii", GetData<uint16_t>(PlayerData::kGameID), ObjectID);
}

void Player::OnConnect(std::shared_ptr<MySQLResult> Result)
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
							SetData<int16_t>(Index, static_cast<int16_t>(std::stoi(Value)));
							break;
						}
						case enum_field_types::MYSQL_TYPE_TINY:
						{
							SetData<int8_t>(Index, static_cast<int8_t>(std::stoi(Value)));
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

void Player::OnDisconnect(const DisconnectReason& Reason)
{
	// TODO: Save player data.
}

void Player::OnInserted(std::shared_ptr<MySQLResult> Result)
{
	SetData<uint64_t>(PlayerData::kMySQLID, static_cast<uint64_t>(Result->GetInsertedID()));
	MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `ID` = ':id' LIMIT 1", { MySQL::GetInstance()->MakeParameter("id", GetMySQLID()) }, &Player::OnConnect, this);
}

void Player::OnObjectEdit(uint32_t ObjectID, ObjectEditionResponse Response, const Point3D<float>& Position, const Point3D<float>& Rotation)
{
	if (Object::IsValid(ObjectID) == true)
	{
		if (Response == ObjectEditionResponse::kFinal)
		{
			CancelEdit();
		}
		else
		{
			Object::SetPosition(ObjectID, Position.X, Position.Y, Position.Z);
			Object::SetRotation(ObjectID, Rotation.X, Rotation.Y, Rotation.Z);
		}
	}
}

void Player::OnObjectSelect(uint32_t ObjectID, uint32_t ModelID, const Point3D<float>& Position)
{
	if (Object::IsValid(ObjectID) == true)
	{
		EditObject(ObjectID);
	}
}

void Player::OnPickUp(int ID)
{
}

void Player::OnSpawn()
{
	SetPosition(1743.0f, -1862.0f, 13.6f);
}

const AdminLevel Player::GetAdminLevel() const
{
	return GetData<AdminLevel>(PlayerData::kAdminLevel);
}

const std::string Player::GetEmail() const
{
	return GetData<std::string>(PlayerData::kEmail);
}

const uint16_t Player::GetGameID() const
{
	return GetData<uint16_t>(PlayerData::kGameID);
}

const uint64_t Player::GetMySQLID() const
{
	return GetData<uint64_t>(PlayerData::kMySQLID);
}

const std::shared_ptr<Vehicle> Player::GetVehicle() const
{
	return Vehicle::Get(static_cast<uint16_t>(sampgdk::GetPlayerVehicleID(GetGameID())));
}

const int32_t Player::GetCash() const
{
	return GetData<int32_t>(PlayerData::kCash);
}

const int64_t Player::GetMoney() const
{
	return GetData<int64_t>(PlayerData::kMoney);
}

const std::string Player::GetName() const
{
	return GetData<std::string>(PlayerData::kName);
}

const std::string Player::GetSalt() const
{
	return GetData<std::string>(PlayerData::kSalt);
}

const PlayerSex Player::GetSex() const
{
	return GetData<PlayerSex>(PlayerData::kSex);
}

void Player::GiveCash(int32_t Amount)
{
	SetData<int>(PlayerData::kCash, GetData<int>(PlayerData::kCash) + Amount);
	sampgdk::GivePlayerMoney(GetGameID(), GetData<int>(PlayerData::kCash));
}

void Player::GiveMoney(int64_t Amount)
{
	SetData<int64_t>(PlayerData::kMoney, GetData<int64_t>(PlayerData::kMoney) + Amount);
}

const bool Player::IsAdmin() const
{
	return GetData<AdminLevel>(PlayerData::kAdminLevel) >= AdminLevel::kLevelOne;
}

const bool Player::IsAuthenticated() const
{
	return GetData<bool>(PlayerData::kAuthenticated);
}

const bool Player::IsInAnyFaction() const
{
	// TODO: Check if the player is in any faction.
	return false;
}

const bool Player::IsInRangeOfPoint(const Point3D<float>& Position, float Range)
{
	return IsInRangeOfPoint(Position.X, Position.Y, Position.Z, Range);
}

const bool Player::IsInRangeOfPoint(float X, float Y, float Z, float Range)
{
	return sampgdk::IsPlayerInRangeOfPoint(GetGameID(), X, Y, Z, Range);
}

const bool Player::IsInVehicle() const
{
	return sampgdk::IsPlayerInAnyVehicle(GetGameID()) && Vehicle::Contains(sampgdk::GetPlayerVehicleID(GetGameID())) == true;
}

const bool Player::IsInVehicle(uint16_t VehicleID) const
{
	return sampgdk::IsPlayerInVehicle(GetGameID(), VehicleID) && Vehicle::Contains(VehicleID) == true;
}

const bool Player::IsLeader() const
{
	// TODO: Check if the player is leader.
	return false;
}

const bool Player::IsSubleader() const
{
	// TODO: Check if the player is subleader.
	return false;
}

const bool Player::Kick() const
{
	return sampgdk::Kick(GetGameID());
}

void Player::SetAdminLevel(AdminLevel Level)
{
	SetData<AdminLevel>(PlayerData::kAdminLevel, Level);
}

void Player::SetCash(int32_t Amount)
{
	SetData<int32_t>(PlayerData::kCash, Amount);

	sampgdk::ResetPlayerMoney(GetGameID());
	sampgdk::GivePlayerMoney(GetGameID(), Amount);
}

void Player::SetMoney(int64_t Amount)
{
	SetData<int64_t>(PlayerData::kMoney, Amount);
}

const bool Player::SetPosition(const Point3D<float>& Position, const float Angle, const uint32_t Interior, const uint32_t VirtualWorld) const
{
	return SetPosition(Position.X, Position.Y, Position.Z, Angle, Interior, VirtualWorld);
}

const bool Player::SetPosition(const float X, const float Y, const float Z, const float Angle, const uint32_t Interior, const uint32_t VirtualWorld) const
{
	auto ID = GetGameID();
	return sampgdk::SetPlayerPos(ID, X, Y, Z) && sampgdk::SetPlayerFacingAngle(ID, Angle) && sampgdk::SetPlayerInterior(ID, Interior) && sampgdk::SetPlayerVirtualWorld(ID, VirtualWorld);
}

bool Player::Spawn()
{
	if (GetData<bool>(PlayerData::kSpectating) == true)
	{
		return ToggleSpectating(false);
	}

	return sampgdk::SpawnPlayer(GetGameID());
}

bool Player::ToggleSpectating(const bool Toggle)
{
	SetData<bool>(PlayerData::kSpectating, Toggle);
	return sampgdk::TogglePlayerSpectating(GetGameID(), Toggle);
}

std::shared_ptr<Dialog> Player::GetDialog(const DialogID& ID)  const
{
	return Dialogs::GetInstance()->Get(ID);
}
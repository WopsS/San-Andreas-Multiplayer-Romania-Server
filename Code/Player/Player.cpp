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

void Player::AttachCameraToObject(int32_t ObjectID)
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

const bool Player::EditObject(uint32_t ObjectID) const
{
	static AMX_NATIVE Native = sampgdk::FindNative("EditDynamicObject");
	return !!sampgdk::InvokeNative(Native, "ii", GetGameID(), ObjectID);
}

void Player::OnConnect(std::shared_ptr<MySQLResult> Result)
{
	if (Result->GetRowCount() > 0) // Player has an account in database, store the information.
	{
		// Load user information from database.

		auto Length = Result->GetFieldCount();

		for (size_t i = 0; i < Length; i++)
		{
			auto Index = static_cast<PlayerData>(i);
			auto Value = Result->GetRowData(Index);

			switch (Index)
			{
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
					SetData(Result->GetField(Index), Index, Value);
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

void Player::OnEnterBuilding(Interior Interior, uint16_t ID)
{
	SetData<::Interior>(PlayerData::kInterior, Interior);
	SetData<uint16_t>(PlayerData::kInteriorID, ID);
}

void Player::OnExitBuilding(Interior Interior)
{
	SetData<::Interior>(PlayerData::kInterior, Interior);
	SetData<uint16_t>(PlayerData::kInteriorID, 0);
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

void Player::OnPickUp(uint32_t ID)
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

const int32_t Player::GetCash() const
{
	return GetData<int32_t>(PlayerData::kCash);
}

std::shared_ptr<House> Player::GetClosestHouse(float Range) const
{
	for (auto i : House::GetList())
	{
		if (IsInRangeOfPoint(i.second->GetEntrance(), Range) == true)
		{
			return i.second;
		}
	}

	return nullptr;
}

const std::string Player::GetEmail() const
{
	return GetData<std::string>(PlayerData::kEmail);
}

const uint16_t Player::GetGameID() const
{
	return GetData<uint16_t>(PlayerData::kGameID);
}

std::shared_ptr<House> Player::GetHouse() const
{
	auto ID = GetMySQLID();

	for (auto i : House::GetList())
	{
		if (i.second->GetOwnerID() == ID)
		{
			return i.second;
		}
	}

	return nullptr;
}

const Interior Player::GetInterior() const
{
	return GetData<Interior>(PlayerData::kInterior);
}

const uint16_t Player::GetInteriorID() const
{
	return GetData<uint16_t>(PlayerData::kInteriorID);
}

const uint64_t Player::GetMySQLID() const
{
	return GetData<uint64_t>(PlayerData::kMySQLID);
}

const std::shared_ptr<Vehicle> Player::GetVehicle() const
{
	return Vehicle::Get(static_cast<uint16_t>(sampgdk::GetPlayerVehicleID(GetGameID())));
}

const int64_t Player::GetMoney() const
{
	return GetData<int64_t>(PlayerData::kMoney);
}

const std::string Player::GetName() const
{
	return GetData<std::string>(PlayerData::kName);
}

const std::string Player::GetPassword() const
{
	return GetData<std::string>(PlayerData::kPassword);
}

const std::string Player::GetPin() const
{
	return GetData<std::string>(PlayerData::kPin);
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
	SetData<int32_t>(PlayerData::kCash, GetData<int32_t>(PlayerData::kCash) + Amount);
	sampgdk::GivePlayerMoney(GetGameID(), GetData<int32_t>(PlayerData::kCash));
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

const bool Player::IsInRangeOfPoint(const Point3D<float>& Position, float Range) const
{
	return IsInRangeOfPoint(Position.X, Position.Y, Position.Z, Range);
}

const bool Player::IsInRangeOfPoint(float X, float Y, float Z, float Range) const
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
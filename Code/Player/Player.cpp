#include <Player/Player.hpp>
#include <Dialog/Dialogs.hpp>

Player::Player(unsigned short ID)
{
	char Name[MAX_PLAYER_NAME + 1];
	sampgdk::GetPlayerName(ID, Name, sizeof(Name));

	std::stringstream StringStream;
	StringStream << Name;

	AddData<unsigned short>(PlayerData::kGameID, ID);
	AddData<std::string>(PlayerData::kName, StringStream.str());
	AddData<bool>(PlayerData::kAuthenticated, false);
}

void Player::AttachCameraToObject(int ObjectID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachCameraToDynamicObject");
	sampgdk::InvokeNative(Native, "ii", GetGameID(), ObjectID);
}

const bool Player::AttachObject(unsigned int ID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToPlayer");
	return !!sampgdk::InvokeNative(Native, "iiffffff", ID, GetGameID(), X, Y, Z, RotationX, RotationY, RotationZ);
}

const void Player::CancelEdit() const
{
	sampgdk::CancelEdit(GetData<unsigned short>(PlayerData::kGameID));
}

const bool Player::EditObject(unsigned int ObjectID) const
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

void Player::OnEnterBuilding(Interior Interior, unsigned short ID)
{
	SetData<::Interior>(PlayerData::kInterior, Interior);
	SetData<unsigned short>(PlayerData::kInteriorID, ID);
}

void Player::OnExitBuilding(Interior Interior)
{
	SetData<::Interior>(PlayerData::kInterior, Interior);
	SetData<unsigned short>(PlayerData::kInteriorID, 0);
}

void Player::OnInserted(std::shared_ptr<MySQLResult> Result)
{
	SetData<unsigned long long>(PlayerData::kMySQLID, static_cast<unsigned long long>(Result->GetInsertedID()));
	MySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `ID` = ':id' LIMIT 1", { MySQL::GetInstance()->MakeParameter("id", GetMySQLID()) }, &Player::OnConnect, this);
}

void Player::OnObjectEdit(unsigned int ObjectID, ObjectEditionResponse Response, const Point3D<float>& Position, const Point3D<float>& Rotation)
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

void Player::OnObjectSelect(unsigned int ObjectID, unsigned int ModelID, const Point3D<float>& Position)
{
	if (Object::IsValid(ObjectID) == true)
	{
		EditObject(ObjectID);
	}
}

void Player::OnPickUp(unsigned int ID)
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

const int Player::GetCash() const
{
	return GetData<int>(PlayerData::kCash);
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

const unsigned short Player::GetGameID() const
{
	return GetData<unsigned short>(PlayerData::kGameID);
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

const unsigned short Player::GetInteriorID() const
{
	return GetData<unsigned short>(PlayerData::kInteriorID);
}

const unsigned long long Player::GetMySQLID() const
{
	return GetData<unsigned long long>(PlayerData::kMySQLID);
}

const std::shared_ptr<Vehicle> Player::GetVehicle() const
{
	return Vehicle::Get(static_cast<unsigned short>(sampgdk::GetPlayerVehicleID(GetGameID())));
}

const long long Player::GetMoney() const
{
	return GetData<long long>(PlayerData::kMoney);
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

void Player::GiveCash(int Amount)
{
	SetData<int>(PlayerData::kCash, GetData<int>(PlayerData::kCash) + Amount);
	sampgdk::GivePlayerMoney(GetGameID(), GetData<int>(PlayerData::kCash));
}

void Player::GiveMoney(long long Amount)
{
	SetData<long long>(PlayerData::kMoney, GetData<long long>(PlayerData::kMoney) + Amount);
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

const bool Player::IsInVehicle(unsigned short VehicleID) const
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

void Player::SetCash(int Amount)
{
	SetData<int>(PlayerData::kCash, Amount);

	sampgdk::ResetPlayerMoney(GetGameID());
	sampgdk::GivePlayerMoney(GetGameID(), Amount);
}

void Player::SetMoney(long long Amount)
{
	SetData<long long>(PlayerData::kMoney, Amount);
}

const bool Player::SetPosition(const Point3D<float>& Position, const float Angle, const unsigned int Interior, const unsigned int VirtualWorld) const
{
	return SetPosition(Position.X, Position.Y, Position.Z, Angle, Interior, VirtualWorld);
}

const bool Player::SetPosition(const float X, const float Y, const float Z, const float Angle, const unsigned int Interior, const unsigned int VirtualWorld) const
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
#pragma once

#include <Dialog/Dialog.hpp>
#include <House/House.hpp>
#include <Player/Enums.hpp>
#include <Vehicle/Vehicle.hpp>

#ifdef SendMessage
#undef SendMessage
#endif

class Player : public Map<uint16_t, Player>, private Data<PlayerData>
{
public:

	Player(uint16_t ID);
	~Player() = default;

	void AttachCameraToObject(int32_t ObjectID);

	const bool AttachObject(uint32_t ID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ);

	const void CancelEdit() const;

	const bool EditObject(uint32_t ObjectID) const;

	const AdminLevel GetAdminLevel() const;

	const int32_t GetCash() const;

	std::shared_ptr<House> GetClosestHouse(float Range = 3.0f) const;

	const std::string GetEmail() const;

	const uint16_t GetGameID() const;

	std::shared_ptr<House> GetHouse() const;

	const Interior GetInterior() const;

	const uint16_t GetInteriorID() const;

	const uint64_t GetMySQLID() const;

	const int64_t GetMoney() const;

	const std::string GetName() const;

	const std::string GetPassword() const;

	const std::string GetPin() const;

	const std::string GetSalt() const;

	const PlayerSex GetSex() const;

	const std::shared_ptr<Vehicle> GetVehicle() const;

	void GiveCash(int32_t Amount);

	void GiveMoney(int64_t Amount);

	const bool IsAdmin() const;

	const bool IsAuthenticated() const;

	const bool IsInAnyFaction() const;

	const bool IsInRangeOfPoint(const Point3D<float>& Position, float Range = 3.0f) const;

	const bool IsInRangeOfPoint(float X, float Y, float Z, float Range = 3.0f) const;

	const bool IsInVehicle() const;

	const bool IsInVehicle(uint16_t VehicleID) const;

	const bool IsLeader() const;

	const bool IsSubleader() const;

	const bool Kick() const;

	void OnConnect(std::shared_ptr<MySQLResult> Result);

	void OnDisconnect(const DisconnectReason& Reason);

	void OnEnterBuilding(Interior Interior, uint16_t ID);

	void OnExitBuilding(Interior Interior);

	void OnInserted(std::shared_ptr<MySQLResult> Result);

	void OnObjectEdit(uint32_t ObjectID, ObjectEditionResponse Response, const Point3D<float>& Position, const Point3D<float>& Rotation);

	void OnObjectSelect(uint32_t ObjectID, uint32_t ModelID, const Point3D<float>& Position);

	void OnPickUp(uint32_t ID);

	void OnSpawn();

	template<typename... Args>
	inline bool SendMessage(Color Color, const std::string& Message, Args&& ...args)
	{
		return SendMessage(static_cast<int32_t>(Color), Message, std::forward<Args>(args)...);
	}

	template<typename... Args>
	inline bool SendMessage(int32_t Color, const std::string& Message, Args&& ...args)
	{
		return sampgdk::SendClientMessage(GetGameID(), Color, fmt::format(Message, std::forward<Args>(args)...).c_str());
	}

	void SetAdminLevel(AdminLevel Level);

	void SetCash(int32_t Amount);

	void SetMoney(int64_t Amount);

	const bool SetPosition(const Point3D<float>& Position, const float Angle = 0.0f, const uint32_t Interior = 0, const uint32_t VirtualWorld = 0) const;

	const bool SetPosition(const float X, const float Y, const float Z, const float Angle = 0.0f, const uint32_t Interior = 0, const uint32_t VirtualWorld = 0) const;

	template<typename... Args>
	inline const bool ShowDialog(const DialogID& ID, Args&& ...args) const
	{
		auto Dialog = Dialogs::GetInstance()->Get(ID);

		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int32_t>(ID), static_cast<int32_t>(Dialog->GetStyle()), Dialog->GetCaption().c_str(), fmt::format(Dialog->GetText(), std::forward<Args>(args)...).c_str(), Dialog->GetButton1().c_str(), Dialog->GetButton2().c_str());
	}

	template<typename... Args>
	inline const bool ShowDialog(const Dialog& Dialog, Args&& ...args) const
	{
		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int32_t>(Dialog.GetID()), static_cast<int32_t>(Dialog.GetStyle()), Dialog.GetCaption().c_str(), fmt::format(Dialog.GetText(), std::forward<Args>(args)...).c_str(), Dialog.GetButton1().c_str(), Dialog.GetButton2().c_str());
	}

	bool Spawn();

	bool ToggleSpectating(const bool Toggle);

private:

	friend class Dialogs;
};
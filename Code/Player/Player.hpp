#pragma once

#include <Dialog/Dialog.hpp>
#include <Player/Enums.hpp>
#include <Vehicle/Vehicle.hpp>

#ifdef SendMessage
#undef SendMessage
#endif

class Player : public Map<unsigned short, Player>, private Data<PlayerData>
{
public:

	Player(unsigned short ID);
	~Player() = default;

	void AttachCameraToObject(int ObjectID);

	const bool AttachObject(unsigned int ID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ);

	const void CancelEdit() const;

	const bool EditObject(unsigned int ObjectID) const;

	const AdminLevel GetAdminLevel() const;

	const std::string GetEmail() const;

	const unsigned short GetGameID() const;

	const unsigned long long GetMySQLID() const;

	const std::shared_ptr<Vehicle> GetVehicle() const;

	const int GetCash() const;

	const long long GetMoney() const;

	const std::string GetName() const;

	const std::string GetSalt() const;

	const PlayerSex GetSex() const;

	void GiveCash(int Amount);

	void GiveMoney(long long Amount);

	const bool IsAdmin() const;

	const bool IsAuthenticated() const;

	const bool IsInAnyFaction() const;

	const bool IsInRangeOfPoint(const Point3D<float>& Position, float Range = 3.0f);

	const bool IsInRangeOfPoint(float X, float Y, float Z, float Range = 3.0f);

	const bool IsInVehicle() const;

	const bool IsInVehicle(unsigned short VehicleID) const;

	const bool IsLeader() const;

	const bool IsSubleader() const;

	const bool Kick() const;

	void OnConnect(std::shared_ptr<MySQLResult> Result);

	void OnDisconnect(const DisconnectReason& Reason);

	void OnInserted(std::shared_ptr<MySQLResult> Result);

	void OnObjectEdit(unsigned int ObjectID, ObjectEditionResponse Response, const Point3D<float>& Position, const Point3D<float>& Rotation);

	void OnObjectSelect(unsigned int ObjectID, unsigned int ModelID, const Point3D<float>& Position);

	void OnPickUp(unsigned int ID);

	void OnSpawn();

	template<typename... Args>
	inline bool SendMessage(Color Color, const std::string& Message, Args&& ...args)
	{
		return SendMessage(static_cast<int>(Color), Message, std::forward<Args>(args)...);
	}

	template<typename... Args>
	inline bool SendMessage(int Color, const std::string& Message, Args&& ...args)
	{
		return sampgdk::SendClientMessage(GetGameID(), Color, fmt::format(Message, std::forward<Args>(args)...).c_str());
	}

	void SetAdminLevel(AdminLevel Level);

	void SetCash(int Amount);

	void SetMoney(long long Amount);

	const bool SetPosition(const Point3D<float>& Position, const float Angle = 0.0f, const unsigned int Interior = 0, const unsigned int VirtualWorld = 0) const;

	const bool SetPosition(const float X, const float Y, const float Z, const float Angle = 0.0f, const unsigned int Interior = 0, const unsigned int VirtualWorld = 0) const;

	template<typename... Args>
	inline const bool ShowDialog(const DialogID& ID, Args&& ...args) const
	{
		auto Dialog = GetDialog(ID);

		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(ID), static_cast<int>(Dialog->GetStyle()), Dialog->GetCaption().c_str(), fmt::format(Dialog->GetText(), std::forward<Args>(args)...).c_str(), Dialog->GetButton1().c_str(), Dialog->GetButton2().c_str());
	}

	template<typename... Args>
	inline const bool ShowDialog(const Dialog& Dialog, Args&& ...args) const
	{
		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(Dialog.GetID()), static_cast<int>(Dialog.GetStyle()), Dialog.GetCaption().c_str(), fmt::format(Dialog.GetText(), std::forward<Args>(args)...).c_str(), Dialog.GetButton1().c_str(), Dialog.GetButton2().c_str());
	}

	bool Spawn();

	bool ToggleSpectating(const bool Toggle);

private:

	friend class Dialogs;

	std::shared_ptr<Dialog> GetDialog(const DialogID& ID) const;
};
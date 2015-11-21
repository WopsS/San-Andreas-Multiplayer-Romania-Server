#pragma once

#include <memory>
#include <unordered_map>

#include <stdafx.hpp>
#include <format.h>
#include <Base/CData.hpp>
#include <Base/CMap.hpp>
#include <Dialog/CDialog.hpp>
#include <Dialog/Enums.hpp>
#include <MySQL/CResult.hpp>
#include <Player/Enums.hpp>

/*
* <remarks>
* Functions like 'GetName' doesn't return a reference to the type because it is a local variable and it doesn't look like this 'const std::string GetName() const;' because if the kName
* doesn't exist in 'm_data' from 'CData' it will be added, so it will change a class member.
* </remakrs>
*/
class CPlayer : public CMap<uint16_t, CPlayer>
{
public:

	CPlayer(uint16_t aID);
	~CPlayer();

	template<typename T>
	inline const bool AddData(PlayerData Index, T Value)
	{
		return m_data.Add(Index, Value);
	}

	void OnConnect(std::shared_ptr<CResult> Result);

	void OnDisconnect(const DisconnectReason& Reason);

	bool OnDialogResponse(const DialogID& ID, const DialogResponse& Response, const uint32_t Item, const std::string& Text);

	void OnInserted(std::shared_ptr<CResult> Result);

	void OnSpawn();

	template<typename T>
	inline const T GetData(PlayerData Index)
	{
		return m_data.Get<T>(Index);
	}

	const std::string GetEmail();

	uint16_t GetGameID();

	uint64_t GetMySQLID();

	const std::string GetName();

	const std::string GetSalt();

	const PlayerSex GetSex();

	bool IsAuthenticated();

	bool Kick();

	template<typename T>
	inline const bool SetData(PlayerData Index, T Value)
	{
		return m_data.Set<T>(Index, Value);
	}

	bool SetPosition(const float X, const float Y, const float Z, const float Angle = 0.0f, const uint32_t Interior = 0, const uint32_t VirtualWorld = 0);

	template<typename... Args>
	inline bool ShowDialog(const DialogID& ID, Args&& ...args)
	{
		auto Dialog = CDialog::Get(ID);

		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(ID), static_cast<int>(Dialog->GetStyle()), Dialog->GetCaption().c_str(),
			fmt::format(Dialog->GetText(), std::forward<Args>(args)...).c_str(), Dialog->GetButton1().c_str(), Dialog->GetButton2().c_str());
	}

	template<typename... Args>
	inline bool ShowDialog(const CDialog& Dialog, Args&& ...args)
	{
		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(Dialog.GetID()), static_cast<int>(Dialog.GetStyle()), Dialog.GetCaption().c_str(), 
			fmt::format(Dialog.GetText(), std::forward<Args>(args)...).c_str(), Dialog.GetButton1().c_str(), Dialog.GetButton2().c_str());
	}

	bool Spawn();

	bool ToggleSpectating(const bool Toggle);

private:

	friend class CMap<uint16_t, CPlayer>;

	CData<PlayerData> m_data;
};
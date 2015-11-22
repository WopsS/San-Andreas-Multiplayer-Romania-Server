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

#ifdef SendMessage
#undef SendMessage
#endif

/*
* <remarks>
* Functions like 'GetName' doesn't return a reference to the type because it is a local variable and it doesn't look like this 'const std::string GetName() const;' because if the kName
* doesn't exist in 'm_data' from 'CData' it will be added, so it will change a class member.
* </remakrs>
*/
class CPlayer : public CMap<uint16_t, CPlayer>, private CData<PlayerData>
{
public:

	CPlayer(uint16_t aID);
	~CPlayer();

	void OnConnect(std::shared_ptr<CResult> Result);

	void OnDisconnect(const DisconnectReason& Reason);

	bool OnDialogResponse(const DialogID& ID, const DialogResponse& Response, const uint32_t Item, const std::string& Text);

	void OnInserted(std::shared_ptr<CResult> Result);

	void OnSpawn();

	bool OnCommand(const std::string& Command);

	const std::string GetEmail() const;

	uint16_t GetGameID() const;

	uint64_t GetMySQLID() const;

	const std::string GetName() const;

	const std::string GetSalt() const;

	const PlayerSex GetSex() const;

	bool IsAuthenticated() const;

	bool Kick() const;

	template<typename... Args>
	bool SendMessage(int Color, const std::string& Message, Args&& ...args)
	{
		return sampgdk::SendClientMessage(GetGameID(), Color, fmt::format(Message, std::forward<Args>(args)...).c_str());
	}

	bool SetPosition(const float X, const float Y, const float Z, const float Angle = 0.0f, const uint32_t Interior = 0, const uint32_t VirtualWorld = 0) const;

	template<typename... Args>
	inline const bool ShowDialog(const DialogID& ID, Args&& ...args) const
	{
		auto Dialog = CDialog::Get(ID);

		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(ID), static_cast<int>(Dialog->GetStyle()), Dialog->GetCaption().c_str(),
			fmt::format(Dialog->GetText(), std::forward<Args>(args)...).c_str(), Dialog->GetButton1().c_str(), Dialog->GetButton2().c_str());
	}

	template<typename... Args>
	inline const bool ShowDialog(const CDialog& Dialog, Args&& ...args) const
	{
		return sampgdk::ShowPlayerDialog(GetGameID(), static_cast<int>(Dialog.GetID()), static_cast<int>(Dialog.GetStyle()), Dialog.GetCaption().c_str(), 
			fmt::format(Dialog.GetText(), std::forward<Args>(args)...).c_str(), Dialog.GetButton1().c_str(), Dialog.GetButton2().c_str());
	}

	bool Spawn();

	bool ToggleSpectating(const bool Toggle);
};
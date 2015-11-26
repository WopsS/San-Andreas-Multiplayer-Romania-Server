#pragma once

#include <memory>
#include <unordered_map>

#include <stdafx.hpp>
#include <format.h>
#include <Base/CData.hpp>
#include <Base/CMap.hpp>
#include <Dialog/CDialog.hpp>
#include <MySQL/CResult.hpp>
#include <Player/Enums.hpp>

#ifdef SendMessage
#undef SendMessage
#endif

class CPlayer : public CMap<uint16_t, CPlayer>, private CData<PlayerData>
{
public:

	CPlayer(uint16_t aID);
	~CPlayer();

	void OnConnect(std::shared_ptr<CResult> Result);

	void OnDisconnect(const DisconnectReason& Reason);

	void OnInserted(std::shared_ptr<CResult> Result);

	void OnSpawn();

	const std::string GetEmail() const;

	uint16_t GetGameID() const;

	uint64_t GetMySQLID() const;

	const std::string GetName() const;

	const std::string GetSalt() const;

	const PlayerSex GetSex() const;

	bool IsAuthenticated() const;

	bool Kick() const;

	template<typename... Args>
	inline bool SendMessage(int Color, const std::string& Message, Args&& ...args)
	{
		return sampgdk::SendClientMessage(GetGameID(), Color, fmt::format(Message, std::forward<Args>(args)...).c_str());
	}

	bool SetPosition(const float X, const float Y, const float Z, const float Angle = 0.0f, const uint32_t Interior = 0, const uint32_t VirtualWorld = 0) const;

	template<typename... Args>
	inline const bool ShowDialog(const DialogID& ID, Args&& ...args) const
	{
		auto Dialog = GetDialog(ID);

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

private:

	friend class CCommands;
	friend class CDialogs;

	std::shared_ptr<CDialog> GetDialog(const DialogID& ID) const;
};
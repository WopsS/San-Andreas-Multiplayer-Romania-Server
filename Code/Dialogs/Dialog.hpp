#pragma once

#include <PermissionFlags.hpp>
#include <Dialogs/Enums.hpp>

class Dialog
{
public:

	Dialog();
	virtual ~Dialog() = default;

	virtual const bool CustomAccess(std::shared_ptr<Player> Player) const = 0;

	virtual void Execute(std::shared_ptr<Player> Player, const DialogResponse& Response, const size_t ItemIndex, const std::string& Text) = 0;

	bool CheckAccess(std::shared_ptr<Player> Player);

	inline const uint32_t GetAccessLevel() const
	{
		return m_accessLevel;
	}

	inline const std::vector<std::string> GetButtons() const
	{
		std::vector<std::string> Result = { m_buttons[0], m_buttons[1] };
		return Result;
	}

	inline const std::string GetCaption() const
	{
		return m_caption;
	}

	inline const DialogID GetID() const
	{
		return m_id;
	}

	inline const DialogStyle GetStyle() const
	{
		return m_style;
	}

	inline const std::string GetText() const
	{
		return m_text;
	}

protected:

	DialogID m_id;

	DialogStyle m_style;

	std::string m_caption;

	std::string m_text;

	std::string m_buttons[2];

	uint32_t m_accessLevel = static_cast<uint32_t>(PermissionFlags::kPlayer);
};
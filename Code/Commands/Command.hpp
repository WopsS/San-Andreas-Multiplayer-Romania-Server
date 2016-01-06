#pragma once

#include <Commands/Parameters.hpp>
#include <Commands/Flags.hpp>
#include <Player/Player.hpp>

class Command
{
public:

	Command() = default;
	virtual ~Command() = default;

	virtual const bool CustomAccess(std::shared_ptr<Player> Player) const = 0;

	virtual void Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters) = 0;

	bool CheckAccess(std::shared_ptr<Player> Player)
	{
		/*
		* Note:
		* 	We don't use an 'if' for 'HasCustomAccess' because if we have a function which check if the player is part of a faction, the command need know if
		* 	the command is for faction's leader or for members without write anything more in the function.
		*/

		if (m_accessLevel & CommandFlags::kPlayer && CustomAccess(Player) == true)
		{
			return true;
		}
		else if ((m_accessLevel & CommandFlags::kMember) && Player->IsInAnyFaction() == true && CustomAccess(Player) == true)
		{
			return true;
		}
		else if ((m_accessLevel & CommandFlags::kSubleader) && Player->IsSubleader() == true && CustomAccess(Player) == true)
		{
			return true;
		}
		else if ((m_accessLevel & CommandFlags::kLeader) && Player->IsLeader() == true && CustomAccess(Player) == true)
		{
			return true;
		}
		else if ((m_accessLevel & CommandFlags::kAdmin) && Player->IsAdmin() == true && CustomAccess(Player) == true)
		{
			return true;
		}

		ShowUnauthorizedMessage(Player);
		return false;
	}

	template<typename... Args>
	inline void ShowUnauthorizedMessage(std::shared_ptr<Player> Player, Args&& ...args)
	{
		Player->SendMessage(Color::kWhite, "ERROR: " + m_unauthorizedMessage, std::forward<Args>(args)...);
	}

	inline void ShowUsageMessages(std::shared_ptr<Player> Player)
	{
		// Send all usage messages to player.
		for (auto& Message : m_usageMessages)
		{
			Player->SendMessage(Color::kWhite, Message);
		}
	}

protected:

	friend class Commands;

	std::vector<std::string> m_names;

	int m_accessLevel = static_cast<int>(CommandFlags::kPlayer);

	std::string m_format;

	std::vector<std::string> m_usageMessages = {};

	std::string m_unauthorizedMessage = "You are not authorized to use this command.";
};
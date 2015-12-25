#include <Command/CCommand.hpp>

CCommand::CCommand(std::vector<std::string> names, int AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess)
	: m_names(names)
	, m_accessLevel(AccessLevel)
	, m_function(Function)
	, m_format(Format)
	, m_usageMessages(UsageMessages)
	, m_unauthorizedMessage(UnauthorizedMessage)
	, m_customAccess(CustomAccess)
{
	if (m_unauthorizedMessage.length() == 0)
	{
		m_unauthorizedMessage = "ERROR: You are not authorized to use this command.";
	}
	else
	{
		m_unauthorizedMessage = "ERROR: " + m_unauthorizedMessage;
	}
}

void CCommand::Execute(std::shared_ptr<CPlayer> Player, std::string& Parameters)
{
	auto CommandParameters = std::make_shared<CCommandParameters>(m_format, Parameters);

	if (CommandParameters->Valid() == false)
	{
		// Send all usage messages to player.
		for (auto& Message : m_usageMessages)
		{
			Player->SendMessage(Colors::kWhite, Message);
			sampgdk::logprintf(Message.c_str());
		}

		return;
	}

	// Call the command's function.
	m_function(Player, CommandParameters);
}

bool CCommand::HasAccess(std::shared_ptr<CPlayer> Player)
{
	/*
		Note: 
			We don't use an 'if' for 'HasCustomAccess' because if we have a function which check if the player is part of a faction, the command need know if 
			the command is for faction's leader or for members without write anything more in the function.
	*/

	if (m_accessLevel & CommandFlags::kPlayer && HasCustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & CommandFlags::kMember) && Player->IsInAnyFaction() == true && HasCustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & CommandFlags::kSubleader) && Player->IsSubleader() == true && HasCustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & CommandFlags::kLeader) && Player->IsLeader() == true && HasCustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & CommandFlags::kAdmin) && Player->IsAdmin() == true && HasCustomAccess(Player) == true)
	{
		return true;
	}

	sampgdk::logprintf(m_unauthorizedMessage.c_str());
	Player->SendMessage(Colors::kWhite, m_unauthorizedMessage);
	return false;
}

bool CCommand::HasCustomAccess(std::shared_ptr<CPlayer> Player)
{
	// Check if the function value is NULL, if it is return true.
	if (m_customAccess == nullptr)
	{
		return true;
	}

	return m_customAccess(Player);
}

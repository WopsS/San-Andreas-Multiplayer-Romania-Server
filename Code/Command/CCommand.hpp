#pragma once

#include <string>
#include <vector>

#include <Base/Types.hpp>
#include <Command/CCommandParameters.hpp>
#include <Command/Flags.hpp>
#include <Player/CPlayer.hpp>

class CCommand
{
public:

	CCommand(std::vector<std::string> names, int AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess);
	CCommand() = default;

	void Execute(std::shared_ptr<CPlayer> Player, std::string& Parameters);

	bool HasAccess(std::shared_ptr<CPlayer> Player);

private:

	friend class CCommands;

	bool HasCustomAccess(std::shared_ptr<CPlayer> Player);

	std::vector<std::string> m_names;

	int m_accessLevel;

	commandfunction_t m_function;

	std::string m_format;

	std::vector<std::string> m_usageMessages;

	std::string m_unauthorizedMessage;

	commandaccess_t m_customAccess;
};
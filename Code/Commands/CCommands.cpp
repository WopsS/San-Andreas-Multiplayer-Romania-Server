#include <Commands/CCommands.hpp>

#include <set>
#include <vector>

#include <Colors.hpp>
#include <Base/CPoint.hpp>
#include <House/CHouse.hpp>
#include <Utilities/Utils.hpp>

// Include commands below in alphabetical order.
#include <Commands/Player/Engine.hpp>
#include <Commands/Player/Test.hpp>

CCommands::CCommands()
{
	Register(std::make_unique<TestCommand>());
	Register(std::make_unique<EngineCommand>());
}

bool CCommands::Execute(std::shared_ptr<CPlayer> Player, const std::string& Command)
{
	auto CommandName = Command;

	// Remove slash from the command name.
	CommandName.erase(0, 1);

	auto Parameters = CommandName;

	// Delete parameters from command.
	auto Position = CommandName.find(" ");

	// Check if in the command exists a space.
	if (Position != std::string::npos)
	{
		CommandName.erase(Position, CommandName.length());
	}

	// Delete command from parameters. If we don't have a space, delete just command text to leave the parameters empty.
	Parameters.erase(0, Position == std::string::npos ? CommandName.length() : CommandName.length() + 1);

	for (auto& i : m_commands)
	{
		if (std::find(i->m_names.begin(), i->m_names.end(), Utils::ToLower(CommandName)) != i->m_names.end())
		{
			// Check if the parameters contains only whitespaces.
			if (Parameters.find_first_not_of(' ') == std::string::npos)
			{
				// Make it empty.
				Parameters = "";

				// Note: If a player type '/command     ' it will take the spaces like a parameters, so with that we will prevent this thing and we guarantee the parameter will not be empty.
			}

			if (i->CheckAccess(Player) == true)
			{
				auto CommandParameters = std::make_shared<CCommandParameters>(i->m_format, Parameters);

				if (CommandParameters->Valid() == true)
				{
					i->Execute(Player, CommandParameters);
				}
				else
				{
					i->ShowUsageMessages(Player);
				}
			}

			return true;
		}
	}

	return false;
}

void CCommands::Register(std::unique_ptr<CCommand> Command)
{
	m_commands.push_back(std::move(Command));
}
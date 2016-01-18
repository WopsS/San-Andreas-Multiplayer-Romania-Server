#include <stdafx.hpp>
#include <Commands/Commands.hpp>
#include <House/House.hpp>

// Include commands below in alphabetical order.
#include <Commands/Player/BuyHouse.hpp>
#include <Commands/Player/Engine.hpp>
#include <Commands/Player/Lock.hpp>
#include <Commands/Player/Test.hpp>

Commands::Commands()
{
	Register(std::make_unique<BuyHouseCommand>());
	Register(std::make_unique<EngineCommand>());
	Register(std::make_unique<LockCommand>());
	Register(std::make_unique<TestCommand>());
	
}

bool Commands::Execute(std::shared_ptr<Player> Player, const std::string& Command)
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
				auto CurrentParameters = std::make_unique<CommandParameters>(i->m_format, Parameters);

				if (CurrentParameters->Valid() == true)
				{
					i->Execute(Player, std::move(CurrentParameters));
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

void Commands::Register(std::unique_ptr<Command> Command)
{
	m_commands.push_back(std::move(Command));
}
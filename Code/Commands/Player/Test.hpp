#pragma once

#include <Commands/Command.hpp>

class TestCommand : public Command
{
public:

	TestCommand();
	~TestCommand() = default;

	const bool CustomAccess(std::shared_ptr<Player> Player) const;

	void Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters);
};
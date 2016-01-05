#pragma once

#include <Commands/Command.hpp>

class TestCommand : public Command
{
public:

	TestCommand();
	~TestCommand() = default;

	const bool CustomAccess(std::shared_ptr<Player> Player) const;

	void Execute(std::shared_ptr<Player> Player, std::shared_ptr<CommandParameters> Parameters);
};
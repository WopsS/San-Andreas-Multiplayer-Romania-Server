#pragma once

#include <Commands/Command.hpp>

class EngineCommand : public Command
{
public:

	EngineCommand();
	~EngineCommand() = default;

	inline const bool CustomAccess(std::shared_ptr<Player> Player) const
	{
		return true;
	}

	void Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters);
};
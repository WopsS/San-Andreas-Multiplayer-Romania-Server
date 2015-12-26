#pragma once

#include <Commands/CCommand.hpp>

class EngineCommand : public CCommand
{
public:

	EngineCommand();
	~EngineCommand() = default;

	inline const bool CustomAccess(std::shared_ptr<CPlayer> Player) const
	{
		return true;
	}

	void Execute(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);
};
#pragma once

#include <Commands/CCommand.hpp>

class EngineCommand : public CCommand
{
public:

	EngineCommand();
	~EngineCommand() = default;

	void Execute(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);
};
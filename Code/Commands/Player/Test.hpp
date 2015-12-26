#pragma once

#include <Commands/CCommand.hpp>

class TestCommand : public CCommand
{
public:

	TestCommand();
	~TestCommand() = default;

	bool CustomAccess(std::shared_ptr<CPlayer> Player);

	void Execute(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);
};
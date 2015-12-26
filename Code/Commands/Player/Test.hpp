#pragma once

#include <Commands/CCommand.hpp>

class TestCommand : public CCommand
{
public:

	TestCommand();
	~TestCommand() = default;

	const bool CustomAccess(std::shared_ptr<CPlayer> Player) const;

	void Execute(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);
};
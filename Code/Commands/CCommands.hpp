#pragma once

#include <Commands/CCommand.hpp>
#include <Player/CPlayer.hpp>

class CCommands : public CSingleton<CCommands>
{
public:

	bool Execute(std::shared_ptr<CPlayer> Player, const std::string& CommandName);

private:

	friend class CSingleton<CCommands>;

	CCommands();
	~CCommands() = default;

	void Register(std::unique_ptr<CCommand> Command);

	std::vector<std::unique_ptr<CCommand>> m_commands;
};
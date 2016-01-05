#pragma once

#include <Commands/Command.hpp>
#include <Player/Player.hpp>

class Commands : public Singleton<Commands>
{
public:

	bool Execute(std::shared_ptr<Player> Player, const std::string& CommandName);

private:

	friend class Singleton<Commands>;

	Commands();
	~Commands() = default;

	void Register(std::unique_ptr<Command> Command);

	std::vector<std::unique_ptr<Command>> m_commands;
};
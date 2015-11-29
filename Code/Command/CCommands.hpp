#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <Base/CSingleton.hpp>
#include <Base/Types.hpp>
#include <Command/CCommandParameters.hpp>
#include <Player/CPlayer.hpp>

class CCommands : public CSingleton<CCommands>
{
public:

	bool Execute(std::shared_ptr<CPlayer> Player, const std::string& Command);

private:

	friend class CSingleton<CCommands>;

	CCommands();
	~CCommands() = default;

	void Register(const std::string& Name, std::initializer_list<std::string> Allias, commandfunction_t Function);
	void Register(const std::string& Name, std::initializer_list<std::string> Allias, const std::string& Format, commandfunction_t Function);

	template<typename F, typename C>
	inline commandfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1, std::placeholders::_2);
	}

	void Test(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);

	void Engine(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);

	void Enter(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);

	std::map<std::vector<std::string>, std::tuple<commandfunction_t, std::string>> m_commands;
};
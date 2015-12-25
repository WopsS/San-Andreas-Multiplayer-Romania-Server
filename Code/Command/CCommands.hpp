#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <Base/CSingleton.hpp>
#include <Base/Types.hpp>
#include <Command/CCommand.hpp>
#include <Player/CPlayer.hpp>

class CCommands : public CSingleton<CCommands>
{
public:

	bool Execute(std::shared_ptr<CPlayer> Player, const std::string& CommandName);

private:

	friend class CSingleton<CCommands>;

	CCommands();
	~CCommands() = default;

	void Register(std::initializer_list<std::string> Names, CommandFlags AccessLevel, commandfunction_t Function, const std::string& UnauthorizedMessage = "", commandaccess_t CustomAccess = nullptr);

	void Register(std::initializer_list<std::string> Names, int AccessLevel, commandfunction_t Function, const std::string& UnauthorizedMessage = "", commandaccess_t CustomAccess = nullptr);

	void Register(std::initializer_list<std::string> Names, CommandFlags AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage = "", commandaccess_t CustomAccess = nullptr);

	void Register(std::initializer_list<std::string> Names, int AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage = "", commandaccess_t CustomAccess = nullptr);

	template<typename F, typename C>
	inline commandfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1, std::placeholders::_2);
	}

	void Test(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);

	void Engine(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters);

	std::vector<std::shared_ptr<CCommand>> m_commands;
};
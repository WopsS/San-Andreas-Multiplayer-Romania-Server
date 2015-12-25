#include <Command/CCommands.hpp>

#include <set>
#include <vector>

#include <Colors.hpp>
#include <Base/CPoint.hpp>
#include <House/CHouse.hpp>
#include <Utilities/Utils.hpp>

CCommands::CCommands()
{
	Register({ "test" }, CommandFlags::kLeader | CommandFlags::kAdmin, Bind(&CCommands::Test, this), std::string("sifsp"), { "/test <string> <integer> <float> <string> <Player ID / name>" }, "", [](std::shared_ptr<CPlayer> Player)->bool { return Player->GetAdminLevel() >= AdminLevel::kLevelFive; });
	Register({ "engine" }, CommandFlags::kPlayer, Bind(&CCommands::Engine, this));
}

void CCommands::Register(std::initializer_list<std::string> Names, CommandFlags AccessLevel, commandfunction_t Function, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess)
{
	Register(Names, static_cast<int>(AccessLevel), Function, std::string(), {}, UnauthorizedMessage, CustomAccess);
}

void CCommands::Register(std::initializer_list<std::string> Names, int AccessLevel, commandfunction_t Function, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess)
{
	Register(Names, AccessLevel, Function, std::string(), {}, UnauthorizedMessage, CustomAccess);
}

void CCommands::Register(std::initializer_list<std::string> Names, CommandFlags AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess)
{
	Register(Names, static_cast<int>(AccessLevel), Function, Format, UsageMessages, UnauthorizedMessage, CustomAccess);
}

void CCommands::Register(std::initializer_list<std::string> Names, int AccessLevel, commandfunction_t Function, const std::string& Format, const std::vector<std::string>& UsageMessages, const std::string& UnauthorizedMessage, commandaccess_t CustomAccess)
{
	std::vector<std::string> NewNames;

	// Add names to the vector and make them lower case.
	for (auto& Name : Names)
	{
		NewNames.push_back(Utils::ToLower(Name));
	}

	m_commands.push_back(std::make_shared<CCommand>(NewNames, AccessLevel, Function, Format, UsageMessages, UnauthorizedMessage, CustomAccess));
}

bool CCommands::Execute(std::shared_ptr<CPlayer> Player, const std::string& Command)
{
	auto CommandName = Command;

	// Remove slash from the command name.
	CommandName.erase(0, 1);

	auto Parameters = CommandName;

	// Delete parameters from command.
	auto Position = CommandName.find(" ");

	// Check if in the command exists a space.
	if (Position != std::string::npos)
	{
		CommandName.erase(Position, CommandName.length());
	}

	// Delete command from parameters. If we don't have a space, delete just command text to leave the parameters empty.
	Parameters.erase(0, Position == std::string::npos ? CommandName.length() : CommandName.length() + 1);

	for (auto& i : m_commands)
	{
		if (std::find(i->m_names.begin(), i->m_names.end(), Utils::ToLower(CommandName)) != i->m_names.end())
		{
			// Check if the parameters contains only whitespaces.
			if (Parameters.find_first_not_of(' ') == std::string::npos)
			{
				// Make it empty.
				Parameters = "";

				// Note: If a player type '/command     ' it will take the spaces like a parameters, so with that we will prevent this thing and we guarantee the parameter will not be empty.
			}

			if (i->HasAccess(Player) == true)
			{
				i->Execute(Player, Parameters);
			}

			return true;
		}
	}

	return false;
}

void CCommands::Test(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters)
{
	auto TargetPlayer = Parameters->GetData<std::shared_ptr<CPlayer>>(4);

	if (TargetPlayer == nullptr)
	{
		Player->SendMessage(0xFFFFFFFF, "CCommands::Test - player is not connected.");
		sampgdk::logprintf("CCommands::Test - player is not connected.");

		return;
	}

	Player->SendMessage(0xFFFFFFFF, "CCommands::Test - {} | {} | {} | {} | {}", 
		Parameters->GetData<std::string>(0), Parameters->GetData<int>(1), Parameters->GetData<float>(2), Parameters->GetData<std::string>(3), TargetPlayer->GetName());

	sampgdk::logprintf("CCommands::Test - %s | %i | %f | %s | %s", 
		Parameters->GetData<std::string>(0).c_str(), Parameters->GetData<int>(1), Parameters->GetData<float>(2), Parameters->GetData<std::string>(3).c_str(), TargetPlayer->GetName().c_str());
}

void CCommands::Engine(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters)
{
	if (Player->IsInVehicle() == false)
	{
		Player->SendMessage(Colors::kWhite, "* You are not in a vehicle.");
		return;
	}

	auto Vehicle = Player->GetVehicle();
	auto CurrentState = Vehicle->GetParameter(VehicleParameters::kEngine);

	// TODO: Show message on range.
	Vehicle->SetParameter(VehicleParameters::kEngine, !CurrentState);
	Player->SendMessage(Colors::kWhite, "* You {} the engine of the vehicle.", CurrentState == false ? "started" : "stopped");
}



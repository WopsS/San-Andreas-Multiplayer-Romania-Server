#include <Command/CCommands.hpp>

#include <set>
#include <vector>

#include <Colors.hpp>
#include <Utilities/Utils.hpp>

CCommands::CCommands()
{
	Register("test", {}, std::string("sifsp"), Bind(&CCommands::Test, this));
	Register("engine", {}, Bind(&CCommands::Engine, this));
}

void CCommands::Register(const std::string & Name, std::initializer_list<std::string> Allias, commandfunction_t Function)
{
	Register(Name, Allias, std::string(), Function);
}

void CCommands::Register(const std::string& Name, std::initializer_list<std::string> Allias, const std::string& Format, commandfunction_t Function)
{
	std::vector<std::string> CommandAllias;
	CommandAllias.push_back(Name);

	if (Allias.size() > 0)
	{
		for (auto& i : Allias)
		{
			CommandAllias.push_back(i);
		}
	}

	m_commands.emplace(CommandAllias, std::make_tuple(Function, Format));
}

bool CCommands::Execute(std::shared_ptr<CPlayer> Player, const std::string& Command)
{
	auto lCommand = Command;

	// Remove slash from the command name.
	lCommand.erase(0, 1);

	auto Parameters = lCommand;

	// Delete parameters from command.
	auto Position = lCommand.find(" ");

	// Check if in the command exists a space.
	if (Position != std::string::npos)
	{
		lCommand.erase(Position, lCommand.length());
	}

	// Delete command from parameters. If we don't have a space, delete just command text to leave the parameters empty.
	Parameters.erase(0, Position == std::string::npos ? lCommand.length() : lCommand.length() + 1);

	for (auto& i : m_commands)
	{
		if (std::find(i.first.begin(), i.first.end(), Utils::ToLower(lCommand)) != i.first.end())
		{
			// Check if the parameters contains only whitespaces.
			if (Parameters.find_first_not_of(' ') == std::string::npos)
			{
				// Make it empty.
				Parameters = "";

				// Note: If a player type '/command     ' it will take the spaces like a parameters, so with that we will prevent this thing and we guarantee the parameter will not be empty.
			}

			// Rebind the command with the new arguments.
			auto CommandFunction = std::bind(std::get<0>(i.second), Player, std::make_shared<CCommandParameters>(std::get<1>(i.second), Parameters));

			// Call the command's function.
			CommandFunction();

			return true;
		}
	}

	return false;
}

void CCommands::Test(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters)
{
	if (Parameters->Valid() == false)
	{
		Player->SendMessage(0xFFFFFFFF, "CCommands::Test - four parameters required.");
		sampgdk::logprintf("CCommands::Test - four parameters required.");

		return;
	}

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
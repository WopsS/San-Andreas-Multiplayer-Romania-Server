#include <Commands/Player/Engine.hpp>

EngineCommand::EngineCommand()
{
	m_names = { "engine" };
}

void EngineCommand::Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters)
{
	if (Player->IsInVehicle() == false)
	{
		Player->SendMessage(Color::kWhite, "* You are not in a vehicle.");
		return;
	}

	auto Vehicle = Player->GetVehicle();
	auto CurrentState = Vehicle->GetParameter(VehicleParameters::kEngine);

	// TODO: Show message on range.
	Vehicle->SetParameter(VehicleParameters::kEngine, !CurrentState);
	Player->SendMessage(Color::kWhite, "* You {} the engine of the vehicle.", CurrentState == false ? "started" : "stopped");
}

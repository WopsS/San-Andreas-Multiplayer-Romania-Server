#include <stdafx.hpp>
#include <Commands/Player/Lock.hpp>

LockCommand::LockCommand()
{
	m_names = { "buyohuse" };
}

const bool LockCommand::CustomAccess(std::shared_ptr<Player> Player) const
{
	return true;
}

void LockCommand::Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters)
{
	auto House = Player->GetHouse();

	if (House == nullptr)
	{
		Player->SendMessage(Color::kFren, "* You don't own house.");
		return;
	}
	else if (Player->IsInRangeOfPoint(House->GetEntrance()) == false && Player->GetInterior() != Interior::kHouse)
	{
		Player->SendMessage(Color::kFren, "* You are not near or in your house.");
		return;
	}

	House->SetDoors(!House->GetLocked());
	Player->SendMessage(Color::kWhite, "* You {} your house.", House->IsLocked() == true ? "locked" : "unlocked");
}

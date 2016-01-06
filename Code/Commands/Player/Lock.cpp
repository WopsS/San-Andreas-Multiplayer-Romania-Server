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
	auto House = Player->GetClosestHouse();
	if (Player->GetPlayerHouse() == 0)
	{
		Player->SendMessage(Color::kWhite, "You don't have house.");
		return;
	}
	if (!Player->GetClosestHouse() || House->GetInterior() != Player->GetInterior())
	{
		Player->SendMessage(Color::kWhite, "You don't can execute this command.");
		return;
	}
	if (House->GetLocked() == true)
	{
		House->SetDoors(false);
	}
	else
	{
		House->SetDoors(true);
	}

}

#include <Commands/Player/BuyHouse.hpp>
#include <House/House.hpp>

BuyHouseCommand::BuyHouseCommand()
{
	m_names = { "buyohuse" };
}

const bool BuyHouseCommand::CustomAccess(std::shared_ptr<Player> Player) const
{
	return true;
}

void BuyHouseCommand::Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters)
{
	auto House = Player->GetClosestHouse();

	if (House == nullptr)
	{
		Player->SendMessage(Color::kWhite, "");
		return;
	}
	if (Player->GetCash() < House->GetPrice())
	{
		Player->SendMessage(Color::kWhite, "You don't have enought money for to buy this house.");
		return;
	}
	if (Player->GetPlayerHouse() > 0)
	{
		Player->SendMessage(Color::kWhite, "You own house already.");
	}

	House->SetOwnerID(Player->GetMySQLID());
	Player->GiveCash(-static_cast<int>(House->GetPrice()));
	
	
}


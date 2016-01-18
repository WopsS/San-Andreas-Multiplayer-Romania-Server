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
		Player->SendMessage(Color::kFren, "* You are not near a house.");
		return;
	}
	else if (Player->GetHouse() != nullptr)
	{
		Player->SendMessage(Color::kFren, "* You own house already.");
		return;
	}

	auto Price = static_cast<int32_t>(House->GetPrice());
	
	if (Player->GetCash() < Price)
	{
		Player->SendMessage(Color::kFren, "* You don't have enought money for to buy this house.");
		return;
	}

	House->SetOwner(Player->GetMySQLID());
	Player->GiveCash(-Price);
	
	Player->SendMessage(Color::kWhite, "* You bought this house for ${}.", Utils::FormatNumber(Price));
}


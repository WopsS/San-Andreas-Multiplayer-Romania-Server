#include <Commands/Player/Test.hpp>

TestCommand::TestCommand()
{
	m_names = { "test" };
	m_accessLevel = static_cast<int32_t>(CommandFlags::kPlayer);
	m_format ="sifsp";
	m_usageMessages = { "/test <string> <integer> <float> <string> <Player ID / name>" };
	m_unauthorizedMessage = "You are not authorized to use this command.";
}

const bool TestCommand::CustomAccess(std::shared_ptr<Player> Player) const
{
	return true;
}

void TestCommand::Execute(std::shared_ptr<Player> Player, std::unique_ptr<CommandParameters> Parameters)
{
	auto TargetPlayer = Parameters->GetAt<std::shared_ptr<::Player>>(4);

	if (TargetPlayer == nullptr)
	{
		Player->SendMessage(0xFFFFFFFF, "Commands::Test - player is not connected.");
		sampgdk::logprintf("Commands::Test - player is not connected.");

		return;
	}

	Player->SendMessage(0xFFFFFFFF, "Commands::Test - {} | {} | {} | {} | {}", Parameters->GetAt<std::string>(0), Parameters->GetAt<int32_t>(1), Parameters->GetAt<float>(2), Parameters->GetAt<std::string>(3), TargetPlayer->GetName());
	sampgdk::logprintf("Commands::Test - %s | %i | %f | %s | %s", Parameters->GetAt<std::string>(0).c_str(), Parameters->GetAt<int32_t>(1), Parameters->GetAt<float>(2), Parameters->GetAt<std::string>(3).c_str(), TargetPlayer->GetName().c_str());
}

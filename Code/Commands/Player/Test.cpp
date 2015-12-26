#include <Commands/Player/Test.hpp>

TestCommand::TestCommand()
{
	m_names = { "test" };
	m_accessLevel = static_cast<int>(CommandFlags::kPlayer);
	m_format ="sifsp";
	m_usageMessages = { "/test <string> <integer> <float> <string> <Player ID / name>" };
	m_unauthorizedMessage = "You are not authorized to use this command.";
}

bool TestCommand::CustomAccess(std::shared_ptr<CPlayer> Player)
{
	return true;
}

void TestCommand::Execute(std::shared_ptr<CPlayer> Player, std::shared_ptr<CCommandParameters> Parameters)
{
	auto TargetPlayer = Parameters->GetData<std::shared_ptr<CPlayer>>(4);

	if (TargetPlayer == nullptr)
	{
		Player->SendMessage(0xFFFFFFFF, "CCommands::Test - player is not connected.");
		sampgdk::logprintf("CCommands::Test - player is not connected.");

		return;
	}

	Player->SendMessage(0xFFFFFFFF, "CCommands::Test - {} | {} | {} | {} | {}", Parameters->GetData<std::string>(0), Parameters->GetData<int>(1), Parameters->GetData<float>(2), Parameters->GetData<std::string>(3), TargetPlayer->GetName());
	sampgdk::logprintf("CCommands::Test - %s | %i | %f | %s | %s", Parameters->GetData<std::string>(0).c_str(), Parameters->GetData<int>(1), Parameters->GetData<float>(2), Parameters->GetData<std::string>(3).c_str(), TargetPlayer->GetName().c_str());
}

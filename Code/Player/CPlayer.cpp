#include <Player/CPlayer.hpp>
#include <sstream>

CPlayer::CPlayer(uint16_t aID)
	: m_ID(aID)
{
	char Name[MAX_PLAYER_NAME + 1];
	sampgdk::GetPlayerName(m_ID, Name, sizeof(Name));

	std::stringstream stringStream;
	stringStream << Name;

	m_name = stringStream.str();
}

CPlayer::~CPlayer()
{
}

void CPlayer::OnConnect(std::shared_ptr<CResult> Result)
{
	// TODO: Store all data about the player.
}

uint16_t CPlayer::GetID() const
{
	return m_ID;
}

const std::string& CPlayer::GetName() const
{
	return m_name;
}

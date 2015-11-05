#include <Player/CPlayer.hpp>

CPlayer::CPlayer(uint16_t aID)
	: m_ID(aID)
{
	sampgdk::logprintf("CPlayer::CPlayer");
}

CPlayer::~CPlayer()
{
	sampgdk::logprintf("CPlayer::~CPlayer");
}

uint16_t CPlayer::GetID() const
{
	return m_ID;
}

#include <House/CHouse.hpp>

CHouse::CHouse(uint16_t aID)
	: m_ID(aID)
{
}

CHouse::~CHouse()
{
}

uint16_t CHouse::GetID() const
{
	return m_ID;
}

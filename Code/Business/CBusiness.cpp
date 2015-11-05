#include <Business/CBusiness.hpp>

CBusiness::CBusiness(uint16_t aID)
	: m_ID(aID)
{
}

CBusiness::~CBusiness()
{
}

uint16_t CBusiness::GetID() const
{
	return m_ID;
}

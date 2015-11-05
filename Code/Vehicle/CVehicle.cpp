#include <Vehicle/CVehicle.hpp>

CVehicle::CVehicle(uint16_t aID)
	: m_ID(aID)
{
}

CVehicle::~CVehicle()
{
}

uint16_t CVehicle::GetID() const
{
	return m_ID;
}

#pragma once

#include <Base/CMap.hpp>

class CHouse : public CMap<uint16_t, CHouse>
{
public:

	uint16_t GetID() const;

private:

	friend class CMap<uint16_t, CHouse>;

	CHouse(uint16_t aID);
	~CHouse();

	uint16_t m_ID;
};
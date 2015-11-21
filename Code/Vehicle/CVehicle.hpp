#pragma once

#include <stdafx.hpp>
#include <Base/CMap.hpp>

class CVehicle : public CMap<uint16_t, CVehicle>
{
public:

	uint16_t GetID() const;

private:

	friend class CMap<uint16_t, CVehicle>;

	CVehicle(uint16_t aID);
	~CVehicle();

	uint16_t m_ID;
};
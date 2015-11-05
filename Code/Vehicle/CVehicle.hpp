#pragma once

#include <stdafx.hpp>
#include <Base/CMap.hpp>

class CVehicle : public CMap<CVehicle>
{
public:

	uint16_t GetID() const;

private:

	friend class CMap<CVehicle>;

	CVehicle(uint16_t aID);
	~CVehicle();

	uint16_t m_ID;
};
#pragma once

#include <Base/CMap.hpp>

class CBusiness : public CMap<CBusiness>
{
public:

	uint16_t GetID() const;

private:

	friend class CMap<CBusiness>;

	CBusiness(uint16_t aID);
	~CBusiness();

	uint16_t m_ID;
};
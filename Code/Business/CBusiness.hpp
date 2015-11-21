#pragma once

#include <cstdint>
#include <Base/CMap.hpp>

class CBusiness : public CMap<uint16_t, CBusiness>
{
public:

	uint16_t GetID() const;

private:

	friend class CMap<uint16_t, CBusiness>;

	CBusiness(uint16_t aID);
	~CBusiness();

	uint16_t m_ID;
};
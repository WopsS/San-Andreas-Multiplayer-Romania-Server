#pragma once

#include <stdafx.hpp>
#include <Base/CMap.hpp>

class CPlayer : public CMap<CPlayer>
{
public:

	CPlayer(uint16_t aID);
	~CPlayer();

	uint16_t GetID() const;

private:

	friend class CMap<CPlayer>;

	

	uint16_t m_ID;
};
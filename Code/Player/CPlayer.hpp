#pragma once

#include <stdafx.hpp>

class CPlayer
{
public:

	CPlayer(uint32_t aID);
	~CPlayer();

private:

	uint32_t m_ID;
};
#pragma once

#include <memory>

#include <stdafx.hpp>
#include <Base/CMap.hpp>
#include <MySQL/CResult.hpp>

class CPlayer : public CMap<CPlayer>
{
public:

	CPlayer(uint16_t aID);
	~CPlayer();

	void OnConnect(std::shared_ptr<CResult> Result);

	uint16_t GetID() const;

	const std::string& GetName() const;

private:

	friend class CMap<CPlayer>;

	uint16_t m_ID;

	std::string m_name;
};
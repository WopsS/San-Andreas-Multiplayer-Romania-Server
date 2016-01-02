#pragma once

#include <Faction/Enums.hpp>

class CFaction : public CMap<uint16_t, CFaction>, private CData<FactionData>
{
public:

	CFaction(uint16_t ID, std::shared_ptr<CResult> Result);
	~CFaction() = default;

	const std::string GetName() const;
};
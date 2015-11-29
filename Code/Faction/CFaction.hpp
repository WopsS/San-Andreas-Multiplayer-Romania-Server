#pragma once

#include <cstdlib>
#include <string>

#include <Base/CData.hpp>
#include <Base/CMap.hpp>
#include <Faction/Enums.hpp>
#include <MySQL/CResult.hpp>

class CFaction : public CMap<uint16_t, CFaction>, private CData<FactionData>
{
public:

	CFaction(uint16_t ID, std::shared_ptr<CResult> Result);
	~CFaction() = default;

	const std::string GetName() const;
};
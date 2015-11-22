#pragma once

#include <cstdint>
#include <memory>

#include <stdafx.hpp>
#include <Base/CMap.hpp>
#include <Base/CData.hpp>
#include <MySQL/CResult.hpp>
#include <Vehicle/Enums.hpp>

class CVehicle : public CMap<uint16_t, CVehicle>, private CData<VehicleData>
{
public:

	CVehicle(uint16_t aID, std::shared_ptr<CResult> Result);
	~CVehicle();

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;
};
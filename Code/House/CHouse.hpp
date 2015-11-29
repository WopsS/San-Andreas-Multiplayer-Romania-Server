#pragma once

#include <cstdint>
#include <memory>

#include <Base/CMap.hpp>
#include <Base/CData.hpp>
#include <House/Enums.hpp>
#include <MySQL/CResult.hpp>

class CHouse : public CMap<uint16_t, CHouse>, private CData<HouseData>
{
public:

	CHouse(uint16_t aID, std::shared_ptr<CResult> Result);
	~CHouse() = default;

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;

private:

	friend class CKeys;

	void Manage();
};
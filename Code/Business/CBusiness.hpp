#pragma once

#include <cstdint>
#include <memory>

#include <Base/CData.hpp>
#include <Base/CMap.hpp>
#include <Business/Enums.hpp>
#include <MySQL/CResult.hpp>

class CBusiness : public CMap<uint16_t, CBusiness>, private CData<BusinessData>
{
public:

	CBusiness(uint16_t ID, std::shared_ptr<CResult> Result);
	~CBusiness() = default;

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;

private:

	friend class CKeys;
};
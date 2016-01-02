#pragma once

#include <Business/Enums.hpp>

class CBusiness : public CMap<uint16_t, CBusiness>, private CData<BusinessData>
{
public:

	CBusiness(uint16_t ID, std::shared_ptr<CResult> Result);
	~CBusiness() = default;

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;

private:

	friend class CKeys;

	void Manage();
};
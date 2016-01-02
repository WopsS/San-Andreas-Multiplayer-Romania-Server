#pragma once

#include <House/Enums.hpp>

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
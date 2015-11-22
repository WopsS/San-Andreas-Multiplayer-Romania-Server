#include <House/CHouse.hpp>

CHouse::CHouse(uint16_t aID, std::shared_ptr<CResult> Result)
{
	SetData<uint16_t>(HouseData::kID, aID);
	SetData<uint64_t>(HouseData::kOwnerID, static_cast<uint64_t>(std::stoull(Result->GetRowData(aID, HouseData::kOwnerID))));
}

CHouse::~CHouse()
{
}

const uint16_t CHouse::GetID() const
{
	return GetData<uint16_t>(HouseData::kID);
}

const uint64_t CHouse::GetOwnerID() const
{
	return GetData<uint64_t>(HouseData::kOwnerID);
}

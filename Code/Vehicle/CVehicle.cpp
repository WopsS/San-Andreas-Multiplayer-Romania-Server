#include <Vehicle/CVehicle.hpp>

CVehicle::CVehicle(uint16_t aID, std::shared_ptr<CResult> Result)
{
	SetData<uint16_t>(VehicleData::kID, aID);
	SetData<uint64_t>(VehicleData::kOwnerID, static_cast<uint64_t>(std::stoull(Result->GetRowData(aID, VehicleData::kOwnerID))));
}

CVehicle::~CVehicle()
{
}

const uint16_t CVehicle::GetID() const
{
	return GetData<uint16_t>(VehicleData::kID);
}

const uint64_t CVehicle::GetOwnerID() const
{
	return GetData<uint64_t>(VehicleData::kOwnerID);
}

#include <Business/CBusiness.hpp>

CBusiness::CBusiness(uint16_t aID, std::shared_ptr<CResult> Result)
{
	SetData<uint16_t>(BusinessData::kID, aID);
	SetData<uint64_t>(BusinessData::kOwnerID, static_cast<uint64_t>(std::stoull(Result->GetRowData(aID, BusinessData::kOwnerID))));
}

CBusiness::~CBusiness()
{
}

const uint16_t CBusiness::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint64_t CBusiness::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

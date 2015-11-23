#include <Vehicle/CVehicle.hpp>

#include <Utilities/Utils.hpp>

CVehicle::CVehicle(uint16_t aID, std::shared_ptr<CResult> Result)
{
	auto Length = static_cast<size_t>(VehicleData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<VehicleData>(i);
		auto Value = Result->GetRowData(aID, Index);

		if (i == static_cast<size_t>(VehicleData::kID))
		{
			SetData<uint64_t>(VehicleData::kID, std::stoull(Value));
		}
		else if (i == static_cast<size_t>(VehicleData::kOwnerID))
		{
			SetData<uint64_t>(VehicleData::kOwnerID, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else
		{
			if (Utils::IsNumber(Value) == true)
			{
				SetData<uint32_t>(Index, std::stoul(Value));
			}
			else
			{
				SetData<std::string>(Index, Value);
			}
		}
	}
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

#include <Vehicle/CVehicle.hpp>

#include <Utilities/Utils.hpp>

CVehicle::CVehicle(uint16_t aID, std::shared_ptr<CResult> Result)
{
	auto Length = static_cast<size_t>(VehicleData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<VehicleData>(i);
		auto Value = Result->GetRowData(aID, Index);

		if (i == static_cast<size_t>(VehicleData::kID) || i == static_cast<size_t>(VehicleData::kOwnerID))
		{
			SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else
		{
			auto IsFloat = Utils::IsFloat(Value);
			auto IsInteger = Utils::IsInteger(Value);
			auto IsString = IsFloat == false && IsInteger == false;

			if (IsString == true)
			{
				SetData<std::string>(Index, Value);
			}
			else if (IsInteger == true) // Check if it is a number after we check if it is as string because if the number is '0' it will return true at 'IsFloat', so probably if it is 0 it is an integer.
			{
				SetData<uint32_t>(Index, std::stoul(Value));
			}
			else if (IsFloat == true)
			{
				SetData<float>(Index, std::stof(Value));
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

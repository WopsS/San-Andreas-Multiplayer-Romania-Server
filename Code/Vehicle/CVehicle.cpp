#include <Vehicle/CVehicle.hpp>

#include <Utilities/Utils.hpp>

CVehicle::CVehicle(uint16_t ID, std::shared_ptr<CResult> Result)
{
	// Let's do that because the result vector is from index 0.
	ID--;

	auto Length = static_cast<size_t>(VehicleData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<VehicleData>(i);
		auto Value = Result->GetRowData(ID, Index);

		if (Index == VehicleData::kID || Index == VehicleData::kOwnerID)
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

CVehicle::CVehicle(int Model, const Point3D<float>& Position, float Rotation, int Color1, int Color2, int RespawnTine, bool Siren)
{
}

const uint16_t CVehicle::GetGameID() const
{
	return GetData<uint16_t>(VehicleData::kGameID);
}

const uint16_t CVehicle::GetMySQLID() const
{
	return GetData<uint16_t>(VehicleData::kID);
}

const uint64_t CVehicle::GetOwnerID() const
{
	return GetData<uint64_t>(VehicleData::kOwnerID);
}

const bool CVehicle::GetParameter(VehicleParameters Parameter) const
{
	return GetParameters()[static_cast<int>(Parameter)] == 1;
}

const std::vector<bool> CVehicle::GetParameters() const
{
	std::vector<int> ParametersInt;
	ParametersInt.resize(7);

	sampgdk::GetVehicleParamsEx(GetGameID(), &ParametersInt[0], &ParametersInt[1], &ParametersInt[2], &ParametersInt[3], &ParametersInt[4], &ParametersInt[5], &ParametersInt[6]);

	std::vector<bool> Parameters;

	for (size_t i = 0; i < ParametersInt.size(); i++)
	{
		Parameters.push_back(ParametersInt[i] == 1);
	}

	return Parameters;
}

const bool CVehicle::SetParameter(VehicleParameters Parameter, bool Status) const
{
	auto Parameters = GetParameters();
	Parameters[static_cast<int>(Parameter)] = Status;

	return sampgdk::SetVehicleParamsEx(GetGameID(), Parameters[0], Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
}

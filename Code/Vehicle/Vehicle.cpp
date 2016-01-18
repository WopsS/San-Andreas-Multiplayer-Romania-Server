#include <stdafx.hpp>
#include <Vehicle/Vehicle.hpp>

Vehicle::Vehicle(std::unique_ptr<MySQLResult> Result)
{
	auto Length = Result->GetFieldCount();

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<VehicleData>(i);
		auto Value = Result->GetRowData(Index);

		switch (Index)
		{
			case VehicleData::kPosition:
			{
				auto X = std::stof(Result->GetRowData(i++));
				auto Y = std::stof(Result->GetRowData(i++));
				auto Z = std::stof(Result->GetRowData(i));

				SetData<Point3D<float>>(Index, Point3D<float>(X, Y, Z));

				break;
			}
			default:
			{
				SetData(Result->GetField(Index), Index, Value);
				break;
			}
		}
	}

	auto Position = GetData<Point3D<float>>(VehicleData::kPosition);
	auto GameID = sampgdk::CreateVehicle(GetModel(), Position.X, Position.Y, Position.Z, GetRotation(), GetColor1(), GetColor2(), GetRespawnTine(), HasSiren());
	
	SetData<uint16_t>(VehicleData::kGameID, GameID);
}

Vehicle::Vehicle(int32_t Model, const Point3D<float>& Position, float Rotation, int32_t Color1, int32_t Color2, int32_t RespawnTine, bool Siren)
{
}

const uint8_t Vehicle::GetColor1() const
{
	return GetData<uint8_t>(VehicleData::kColor1);
}

const uint8_t Vehicle::GetColor2() const
{
	return GetData<uint8_t>(VehicleData::kColor2);
}

const uint16_t Vehicle::GetGameID() const
{
	return GetData<uint16_t>(VehicleData::kGameID);
}

const uint16_t Vehicle::GetMySQLID() const
{
	return GetData<uint16_t>(VehicleData::kID);
}

const uint64_t Vehicle::GetOwnerID() const
{
	return GetData<uint64_t>(VehicleData::kOwnerID);
}

const uint16_t Vehicle::GetModel() const
{
	return GetData<uint16_t>(VehicleData::kModel);
}

const bool Vehicle::GetParameter(VehicleParameters Parameter) const
{
	return GetParameters()[static_cast<uint16_t>(Parameter)] == 1;
}

const std::vector<bool> Vehicle::GetParameters() const
{
	std::vector<int32_t> ParametersInt;
	ParametersInt.resize(7);

	sampgdk::GetVehicleParamsEx(GetGameID(), &ParametersInt[0], &ParametersInt[1], &ParametersInt[2], &ParametersInt[3], &ParametersInt[4], &ParametersInt[5], &ParametersInt[6]);

	std::vector<bool> Parameters;

	for (size_t i = 0; i < ParametersInt.size(); i++)
	{
		Parameters.push_back(ParametersInt[i] == 1);
	}

	return Parameters;
}

const Point3D<float> Vehicle::GetPosition() const
{
	return GetData<Point3D<float>>(VehicleData::kPosition);
}

const uint32_t Vehicle::GetRespawnTine() const
{
	return GetData<uint32_t>(VehicleData::kRespawnTime);
}

const float Vehicle::GetRotation() const
{
	return GetData<float>(VehicleData::kRotation);
}

const bool Vehicle::HasSiren() const
{
	return GetData<bool>(VehicleData::kSiren);
}

const bool Vehicle::SetParameter(VehicleParameters Parameter, bool Status) const
{
	auto Parameters = GetParameters();
	Parameters[static_cast<uint8_t>(Parameter)] = Status;

	return sampgdk::SetVehicleParamsEx(GetGameID(), Parameters[0], Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
}

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
	
	SetData<unsigned short>(VehicleData::kGameID, GameID);
}

Vehicle::Vehicle(int Model, const Point3D<float>& Position, float Rotation, int Color1, int Color2, int RespawnTine, bool Siren)
{
}

const unsigned char Vehicle::GetColor1() const
{
	return GetData<unsigned char>(VehicleData::kColor1);
}

const unsigned char Vehicle::GetColor2() const
{
	return GetData<unsigned char>(VehicleData::kColor2);
}

const unsigned short Vehicle::GetGameID() const
{
	return GetData<unsigned short>(VehicleData::kGameID);
}

const unsigned short Vehicle::GetMySQLID() const
{
	return GetData<unsigned short>(VehicleData::kID);
}

const unsigned long long Vehicle::GetOwnerID() const
{
	return GetData<unsigned long long>(VehicleData::kOwnerID);
}

const unsigned short Vehicle::GetModel() const
{
	return GetData<unsigned short>(VehicleData::kModel);
}

const bool Vehicle::GetParameter(VehicleParameters Parameter) const
{
	return GetParameters()[static_cast<unsigned short>(Parameter)] == 1;
}

const std::vector<bool> Vehicle::GetParameters() const
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

const Point3D<float> Vehicle::GetPosition() const
{
	return GetData<Point3D<float>>(VehicleData::kPosition);
}

const unsigned int Vehicle::GetRespawnTine() const
{
	return GetData<unsigned int>(VehicleData::kRespawnTime);
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
	Parameters[static_cast<unsigned char>(Parameter)] = Status;

	return sampgdk::SetVehicleParamsEx(GetGameID(), Parameters[0], Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
}

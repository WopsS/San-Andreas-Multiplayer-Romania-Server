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

		switch (Index)
		{
			case VehicleData::kID:
			case VehicleData::kOwnerID:
			{
				SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
				break;
			}
			case VehicleData::kPosition:
			{
				auto X = std::stof(Result->GetRowData(ID, i++));
				auto Y = std::stof(Result->GetRowData(ID, i++));
				auto Z = std::stof(Result->GetRowData(ID, i++));
				auto Rotation = std::stof(Result->GetRowData(ID, i));

				SetData<Point3D<float>>(Index, Point3D<float>(X, Y, Z));
				SetData<float>(VehicleData::kRotation, Rotation);

				break;
			}
			case VehicleData::kSiren:
			{
				SetData<bool>(Index, !!std::stoi(Result->GetRowData(ID, i++)));
				break;
			}
			default:
			{
				switch (Result->GetFieldType(Index))
				{
					case enum_field_types::MYSQL_TYPE_DOUBLE:
					{
						SetData<double>(Index, std::stod(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_FLOAT:
					{
						SetData<float>(Index, std::stof(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_INT24:
					case enum_field_types::MYSQL_TYPE_LONG:
					{
						SetData<int32_t>(Index, std::stoi(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_LONGLONG:
					{
						SetData<int64_t>(Index, std::stoll(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_SHORT:
					{
						SetData<int16_t>(Index, std::stoi(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_TINY:
					{
						SetData<int8_t>(Index, std::stoi(Value));
						break;
					}
					default:
					{
						SetData<std::string>(Index, Value);
						break;
					}
				}

				break;
			}
		}
	}

	auto Position = GetData<Point3D<float>>(VehicleData::kPosition);

	SetData<uint16_t>(VehicleData::kGameID, sampgdk::CreateVehicle(GetData<uint16_t>(VehicleData::kModel), Position.X, Position.Y, Position.Z, GetData<float>(VehicleData::kRotation), 
		GetData<uint32_t>(VehicleData::kColor1), GetData<uint32_t>(VehicleData::kColor2), GetData<uint32_t>(VehicleData::kRespawnTime), GetData<bool>(VehicleData::kSiren)));
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
	return GetParameters()[static_cast<uint16_t>(Parameter)] == 1;
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
	Parameters[static_cast<uint8_t>(Parameter)] = Status;

	return sampgdk::SetVehicleParamsEx(GetGameID(), Parameters[0], Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
}

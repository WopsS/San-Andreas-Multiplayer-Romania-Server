#include <Faction/CFaction.hpp>

#include <Base/CPoint.hpp>
#include <Utilities/Utils.hpp>

CFaction::CFaction(uint16_t ID, std::shared_ptr<CResult> Result)
{
	// Let's do that because the result vector is from index 0.
	ID--;

	auto Length = static_cast<uint8_t>(FactionData::kEndMySQL);

	for (uint8_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<FactionData>(i);
		auto Value = Result->GetRowData(ID, Index);

		switch (Index)
		{
			case FactionData::kID:
			{
				SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
				break;
			}
			case FactionData::kEnterance:
			case FactionData::kExit:
			{
				auto X = std::stof(Result->GetRowData(ID, i++));
				auto Y = std::stof(Result->GetRowData(ID, i++));
				auto Z = std::stof(Result->GetRowData(ID, i));

				SetData<Point3D<float>>(Index, Point3D<float>(X, Y, Z));
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
						SetData<int16_t>(Index, static_cast<int16_t>(std::stoi(Value)));
						break;
					}
					case enum_field_types::MYSQL_TYPE_TINY:
					{
						SetData<int8_t>(Index, static_cast<int8_t>(std::stoi(Value)));
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
}

const std::string CFaction::GetName() const
{
	return GetData<std::string>(FactionData::kName);
}

#include <Faction/Faction.hpp>

Faction::Faction(std::unique_ptr<MySQLResult> Result)
{
	auto Length = Result->GetFieldCount();

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<FactionData>(i);
		auto Value = Result->GetRowData(Index);

		switch (Index)
		{
			case FactionData::kID:
			{
				SetData<unsigned long long>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
				break;
			}
			case FactionData::kEnterance:
			case FactionData::kExit:
			{
				auto X = std::stof(Result->GetRowData(i++));
				auto Y = std::stof(Result->GetRowData(i++));
				auto Z = std::stof(Result->GetRowData(i));

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
						SetData<int>(Index, std::stoi(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_LONGLONG:
					{
						SetData<long long>(Index, std::stoll(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_SHORT:
					{
						SetData<short>(Index, static_cast<short>(std::stoi(Value)));
						break;
					}
					case enum_field_types::MYSQL_TYPE_TINY:
					{
						SetData<signed char>(Index, static_cast<signed char>(std::stoi(Value)));
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

const std::string Faction::GetName() const
{
	return GetData<std::string>(FactionData::kName);
}

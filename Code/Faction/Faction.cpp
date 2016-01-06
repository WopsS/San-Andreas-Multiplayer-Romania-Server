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
			case FactionData::kEntrance:
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
				SetData(Result->GetField(Index), Index, Value);
				break;
			}
		}
	}
}

const Point3D<float> Faction::GetEntrance() const
{
	return GetData<Point3D<float>>(FactionData::kEntrance);
}

const Point3D<float> Faction::GetExit() const
{
	return GetData<Point3D<float>>(FactionData::kExit);
}

const unsigned short Faction::GetID() const
{
	return GetData<unsigned short>(FactionData::kID);
}

const std::string Faction::GetName() const
{
	return GetData<std::string>(FactionData::kName);
}

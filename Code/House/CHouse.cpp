#include <House/CHouse.hpp>

#include <Base/CPoint.hpp>
#include <Utilities/Utils.hpp>

CHouse::CHouse(uint16_t aID, std::shared_ptr<CResult> Result)
{
	auto Length = static_cast<size_t>(HouseData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<HouseData>(i);
		auto Value = Result->GetRowData(aID, Index);

		if (i == static_cast<size_t>(HouseData::kID))
		{
			SetData<uint64_t>(HouseData::kID, std::stoull(Value));
		}
		else if (i == static_cast<size_t>(HouseData::kOwnerID))
		{
			SetData<uint64_t>(HouseData::kOwnerID, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (i == static_cast<size_t>(HouseData::kEntrance))
		{
			auto X = std::stof(Result->GetRowData(aID, i++));
			auto Y = std::stof(Result->GetRowData(aID, i++));
			auto Z = std::stof(Result->GetRowData(aID, i));

			SetData<Point3D<float>>(HouseData::kEntrance, Point3D<float>(X, Y, Z));
		}
		else if (i == static_cast<size_t>(HouseData::kExit))
		{
			auto X = std::stof(Result->GetRowData(aID, i++));
			auto Y = std::stof(Result->GetRowData(aID, i++));
			auto Z = std::stof(Result->GetRowData(aID, i));

			SetData<Point3D<float>>(HouseData::kExit, Point3D<float>(X, Y, Z));
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

CHouse::~CHouse()
{
}

const uint16_t CHouse::GetID() const
{
	return GetData<uint16_t>(HouseData::kID);
}

const uint64_t CHouse::GetOwnerID() const
{
	return GetData<uint64_t>(HouseData::kOwnerID);
}

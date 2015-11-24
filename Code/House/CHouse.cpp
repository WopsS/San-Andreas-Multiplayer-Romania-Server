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

		if (i == static_cast<size_t>(HouseData::kID) || i == static_cast<size_t>(HouseData::kOwnerID))
		{
			SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (i == static_cast<size_t>(HouseData::kEntrance) || i == static_cast<size_t>(HouseData::kExit))
		{
			auto X = std::stof(Result->GetRowData(aID, i++));
			auto Y = std::stof(Result->GetRowData(aID, i++));
			auto Z = std::stof(Result->GetRowData(aID, i));

			SetData<Point3D<float>>(Index, Point3D<float>(X, Y, Z));
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

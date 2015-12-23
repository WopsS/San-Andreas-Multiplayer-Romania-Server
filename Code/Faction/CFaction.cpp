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

		if (Index == FactionData::kID)
		{
			SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (Index == FactionData::kEnterance || Index == FactionData::kExit)
		{
			auto X = std::stof(Result->GetRowData(ID, i++));
			auto Y = std::stof(Result->GetRowData(ID, i++));
			auto Z = std::stof(Result->GetRowData(ID, i));

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

const std::string CFaction::GetName() const
{
	return GetData<std::string>(FactionData::kName);
}

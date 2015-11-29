#include <Business/CBusiness.hpp>

#include <Streamer/Pickup.hpp>
#include <Streamer/TextLabel.hpp>
#include <Streamer/MapIcon.hpp>

#include <Base/CPoint.hpp>
#include <Utilities/Utils.hpp>

CBusiness::CBusiness(uint16_t ID, std::shared_ptr<CResult> Result)
{
	// Let's do that because the result vector is from index 0.
	ID--;

	auto Length = static_cast<size_t>(BusinessData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<BusinessData>(i);
		auto Value = Result->GetRowData(ID, Index);

		if (Index == BusinessData::kID || Index == BusinessData::kOwnerID)
		{
			SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (Index == BusinessData::kEnterance || Index == BusinessData::kExit)
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
	
	auto Entrance = GetData<Point3D<float>>(BusinessData::kEnterance);
	auto Exit = GetData<Point3D<float>>(BusinessData::kExit);
	auto OwnerID = GetData<uint16_t>(BusinessData::kOwnerID);

	Pickup::Create(1239, 23, Entrance);

	TextLabel::Create(OwnerID == 0 ? "Bizz de vanzare" : "Bizz cumarat", 0xFFFFFF, Entrance);

	uint16_t IconID = 0;

	switch (GetData<BusinessType>(BusinessData::kType))
	{
		case BusinessType::kBank:
		{
			IconID = 32;
		}
	}
	SetData<uint32_t>(BusinessData::kIconID, MapIcon::Create(Entrance, IconID));
}

const uint16_t CBusiness::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint64_t CBusiness::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

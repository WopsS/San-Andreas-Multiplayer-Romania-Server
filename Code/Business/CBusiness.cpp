#include <Business/CBusiness.hpp>

#include <Base/CPoint.hpp>
#include <Streamer/MapIcon.hpp>
#include <Streamer/Pickup.hpp>
#include <Streamer/TextLabel.hpp>
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
		else if (Index == BusinessData::kType)
		{
			SetData<BusinessType>(Index, static_cast<BusinessType>(std::stoi(Value)));
		}
		else if (Index == BusinessData::kEntrance || Index == BusinessData::kExit)
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
	
	Manage();
}

const uint16_t CBusiness::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint64_t CBusiness::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

void CBusiness::Manage()
{
	uint16_t MapIconID;

	switch (GetData<BusinessType>(BusinessData::kType))
	{
		case BusinessType::kBank:
		{
			MapIconID = 52;
			break;
		}
		case BusinessType::kGunShop:
		{
			MapIconID = 6;
			break;
		}
		default:
		{
			MapIconID = 36;
			break;
		}
	}

	std::string Text;

	// TODO: Create a function to format the number with comma, eg.: 1000 => 1,000.

	if (GetData<uint64_t>(BusinessData::kOwnerID) == 0)
	{
		Text = fmt::format("Business {}\nThis business is for sale\nName: {FFFFFF}{}\n{0F90FA}Price: {FFFFFF}${}\n{0F90FA}Level: {FFFFFF}{}\n{0F90FA}to buy this business type /COMMAND_HERE",
			GetData<uint64_t>(BusinessData::kID), GetData<uint64_t>(BusinessData::kName), GetData<uint64_t>(BusinessData::kPrice), GetData<uint64_t>(BusinessData::kLevel));
	}
	else
	{
		// TODO: Check if the business is locked and set a specific message.
		Text = fmt::format("Business {}\n{0F90FA}Name: {FFFFFF}{}\n{0F90FA}Owner: {FFFFFF}{}\n{0F90FA}Fee: {FFFFFF}${}", GetData<uint64_t>(BusinessData::kID), GetData<uint64_t>(BusinessData::kName), 
			GetData<uint64_t>(BusinessData::kOwnerID), GetData<uint64_t>(BusinessData::kPayout));
	}

	auto Entrance = GetData<Point3D<float>>(BusinessData::kEntrance);
	auto Exit = GetData<Point3D<float>>(BusinessData::kExit);

	SetData<uint32_t>(BusinessData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<uint32_t>(BusinessData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<uint32_t>(BusinessData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

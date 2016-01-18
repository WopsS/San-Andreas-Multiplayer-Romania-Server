#include <stdafx.hpp>
#include <Business/Business.hpp>

Business::Business(std::unique_ptr<MySQLResult> Result)
{
	auto Length = Result->GetFieldCount();

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<BusinessData>(i);
		auto Value = Result->GetRowData(Index);

		switch (Index)
		{
			case BusinessData::kType:
			{
				SetData<BusinessType>(Index, static_cast<BusinessType>(std::stoi(Value)));
				break;
			}
			case BusinessData::kEntrance: 
			case BusinessData::kExit:
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
	
	Manage();
}

const Point3D<float> Business::GetEntrance() const
{
	return GetData<Point3D<float>>(BusinessData::kEntrance);
}

const Point3D<float> Business::GetExit() const
{
	return GetData<Point3D<float>>(BusinessData::kExit);
}

const uint16_t Business::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint8_t Business::GetInterior() const
{
	return GetData<uint8_t>(BusinessData::kInterior);
}

const uint8_t Business::GetLevel() const
{
	return GetData<uint8_t>(BusinessData::kLevel);
}

const std::string Business::GetName() const
{
	return GetData<std::string>(BusinessData::kName);
}

const uint64_t Business::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

const uint32_t Business::GetPayout() const
{
	return GetData<uint32_t>(BusinessData::kPayout);
}

const uint32_t Business::GetPrice() const
{
	return GetData<uint32_t>(BusinessData::kPrice);
}

const BusinessType Business::GetType() const
{
	return GetData<BusinessType>(BusinessData::kType);
}

const uint32_t Business::GetVirtualWorld() const
{
	return GetData<uint32_t>(BusinessData::kVirtualWorld);
}

const bool Business::IsLocked() const
{
	return GetData<bool>(BusinessData::kLocked);
}

void Business::Manage()
{
	uint32_t MapIconID;

	switch (GetType())
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

	if (GetOwnerID() == 0)
	{
		Text = fmt::format("Business {}\nThis business is for sale\nName: {{FFFFFF}}{}\n{{0F90FA}}Price: {{FFFFFF}}${}\n{{0F90FA}}Level: {{FFFFFF}}{}\n{{0F90FA}}to buy this business type /COMMAND_HERE", GetID(), GetName(), Utils::FormatNumber(GetPrice()), GetLevel());
	}
	else
	{
		// TODO: Check if the business is locked and set a specific message.
		Text = fmt::format("Business {}\n{{0F90FA}}Name: {{FFFFFF}}{}\n{{0F90FA}}Owner: {{FFFFFF}}{}\n{{0F90FA}}Fee: {{FFFFFF}}${}", GetID(), GetName(), GetOwnerID(), GetPayout());
	}

	auto Entrance = GetEntrance();
	auto Exit = GetExit();

	SetData<uint32_t>(BusinessData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<uint32_t>(BusinessData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<uint32_t>(BusinessData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

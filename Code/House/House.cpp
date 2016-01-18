#include <House/House.hpp>

House::House(std::unique_ptr<MySQLResult> Result)
{
	auto Length = Result->GetFieldCount();

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<HouseData>(i);
		auto Value = Result->GetRowData(Index);

		switch (Index)
		{
			case HouseData::kEntrance:
			case HouseData::kExit:
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

const Point3D<float> House::GetEntrance() const
{
	return GetData<Point3D<float>>(HouseData::kEntrance);
}

const Point3D<float> House::GetExit() const
{
	return GetData<Point3D<float>>(HouseData::kExit);
}

const uint16_t House::GetID() const
{
	return GetData<uint16_t>(HouseData::kID);
}

const uint8_t House::GetInterior() const
{
	return GetData<uint8_t>(HouseData::kInterior);
}

const uint8_t House::GetLevel() const
{
	return GetData<uint8_t>(HouseData::kLevel);
}

const bool House::GetLocked() const
{
	return GetData<bool>(HouseData::kLocked);
}

const uint64_t House::GetOwnerID() const
{
	return GetData<uint64_t>(HouseData::kOwnerID);
}

const uint32_t House::GetPrice() const
{
	return GetData<uint32_t>(HouseData::kPrice);
}

const uint32_t House::GetRentPrice() const
{
	return GetData<uint32_t>(HouseData::kRentPrice);
}

const uint32_t House::GetVirtualWorld() const
{
	return GetData<uint32_t>(HouseData::kVirtualWorld);
}

const bool House::IsLocked() const
{
	return GetData<bool>(HouseData::kLocked);
}

const bool House::IsOwned() const
{
	return GetOwnerID() > 0;
}

void House::SetDoors(bool Status)
{
	SetData<bool>(HouseData::kLocked, Status);
}

void House::SetOwner(uint64_t ID)
{
	SetData<uint64_t>(HouseData::kOwnerID, ID);
}

void House::Manage()
{
	uint16_t MapIconID;
	std::string Text;

	if (GetOwnerID() == 0)
	{
		Text = fmt::format("{{FFFFFF}}This house is for sale\n{{0F90FA}}Price: {{FFFFFF}}${}\n{{0F90FA}}Level: {{FFFFFF}}{}\n{{0F90FA}}to buy this house type /COMMAND_HERE.", GetID(), Utils::FormatNumber(GetPrice()), GetLevel());

		MapIconID = 31;
	}
	else
	{
		// TODO: Check if the house is locked and set a specific message, also check if it can be rented.
		Text = fmt::format("{{FFFFFF}}House %i\n{{0F90FA}}Owner: {{FFFFFF}}%s\n{{0F90FA}}Level: {{FFFFFF}}%i", GetID(), GetOwnerID());

		MapIconID = 32;
	}

	auto Entrance = GetEntrance();
	auto Exit = GetExit();

	SetData<uint32_t>(HouseData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<uint32_t>(HouseData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<uint32_t>(HouseData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

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

const unsigned short House::GetID() const
{
	return GetData<unsigned short>(HouseData::kID);
}

const unsigned char House::GetInterior() const
{
	return GetData<unsigned char>(HouseData::kInterior);
}

const unsigned char House::GetLevel() const
{
	return GetData<unsigned char>(HouseData::kLevel);
}

const bool House::GetLocked() const
{
	return GetData<bool>(HouseData::kLocked);
}

const unsigned long long House::GetOwnerID() const
{
	return GetData<unsigned long long>(HouseData::kOwnerID);
}

const unsigned int House::GetPrice() const
{
	return GetData<unsigned int>(HouseData::kPrice);
}

const unsigned int House::GetRentPrice() const
{
	return GetData<unsigned int>(HouseData::kRentPrice);
}

const unsigned int House::GetVirtualWorld() const
{
	return GetData<unsigned int>(HouseData::kVirtualWorld);
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

void House::SetOwner(unsigned long long ID)
{
	SetData<unsigned long long>(HouseData::kOwnerID, ID);
}

void House::Manage()
{
	unsigned short MapIconID;
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

	SetData<unsigned int>(HouseData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<unsigned int>(HouseData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<unsigned int>(HouseData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

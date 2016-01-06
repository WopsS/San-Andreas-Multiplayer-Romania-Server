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
			case HouseData::kID:
			case HouseData::kOwnerID:
			{
				SetData<unsigned long long>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
				break;
			}
			case HouseData::kEntrance:
			case HouseData::kExit:
			{
				auto X = std::stof(Result->GetRowData(i++));
				auto Y = std::stof(Result->GetRowData(i++));
				auto Z = std::stof(Result->GetRowData(i));

				SetData<Point3D<float>>(Index, Point3D<float>(X, Y, Z));
				break;
			}
			case HouseData::kLocked:
			{
				SetData<bool>(Index, !!std::stoi(Value));
				break;
			}
			case HouseData::kRentPrice:
			{
				SetData<unsigned short>(Index, Value.length() == 0 ? 0 : std::stoi(Value));
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

	Manage();
}

const Point3D<float> House::GetExit() const
{
	return GetData<Point3D<float>>(HouseData::kExit);
}

const Point3D<float> House::GetEntrance() const
{
	return GetData<Point3D<float>>(HouseData::kEntrance);
}

const unsigned short House::GetID() const
{
	return GetData<unsigned short>(HouseData::kID);
}

const unsigned long long House::GetOwnerID() const
{
	return GetData<unsigned long long>(HouseData::kOwnerID);
}

const bool House::IsLocked() const
{
	return GetData<bool>(HouseData::kLocked);
}

void House::Manage()
{
	unsigned short MapIconID;
	std::string Text;

	// TODO: Create a function to format the number with comma, eg.: 1000 => 1,000.

	if (GetData<unsigned long long>(HouseData::kOwnerID) == 0)
	{
		Text = fmt::format("{FFFFFF}This house is for sale\n{0F90FA}Price: {FFFFFF}${}\n{0F90FA}Level: {FFFFFF}{}\n{0F90FA}to buy this house type /COMMAND_HERE.",
			GetData<unsigned long long>(HouseData::kID), GetData<unsigned long long>(HouseData::kPrice), GetData<unsigned long long>(HouseData::kLevel));

		MapIconID = 31;
	}
	else
	{
		// TODO: Check if the house is locked and set a specific message, also check if it can be rented.
		Text = fmt::format("{FFFFFF}House %i\n{0F90FA}Owner: {FFFFFF}%s\n{0F90FA}Level: {FFFFFF}%i", GetData<unsigned long long>(HouseData::kID), GetData<unsigned long long>(HouseData::kOwnerID));

		MapIconID = 32;
	}

	auto Entrance = GetData<Point3D<float>>(HouseData::kEntrance);
	auto Exit = GetData<Point3D<float>>(HouseData::kExit);

	SetData<unsigned int>(HouseData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<unsigned int>(HouseData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<unsigned int>(HouseData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

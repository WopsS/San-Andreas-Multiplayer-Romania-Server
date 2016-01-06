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
			case BusinessData::kID:
			case BusinessData::kOwnerID:
			{
				SetData<unsigned long long>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
				break;
			}
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
			case BusinessData::kLocked:
			{
				SetData<bool>(Index, !!std::stoi(Value));
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

const Point3D<float> Business::GetExit() const
{
	return GetData<Point3D<float>>(BusinessData::kExit);
}

const Point3D<float> Business::GetEntrance() const
{
	return GetData<Point3D<float>>(BusinessData::kEntrance);
}

const unsigned short Business::GetID() const
{
	return GetData<unsigned short>(BusinessData::kID);
}

const unsigned long long Business::GetOwnerID() const
{
	return GetData<unsigned long long>(BusinessData::kOwnerID);
}

const bool Business::IsLocked() const
{
	return GetData<bool>(BusinessData::kLocked);
}

void Business::Manage()
{
	unsigned short MapIconID;

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

	if (GetOwnerID() == 0)
	{
		Text = fmt::format("Business {}\nThis business is for sale\nName: {FFFFFF}{}\n{0F90FA}Price: {FFFFFF}${}\n{0F90FA}Level: {FFFFFF}{}\n{0F90FA}to buy this business type /COMMAND_HERE", GetData<unsigned long long>(BusinessData::kID), GetData<std::string>(BusinessData::kName), GetData<unsigned long long>(BusinessData::kPrice), GetData<unsigned long long>(BusinessData::kLevel));
	}
	else
	{
		// TODO: Check if the business is locked and set a specific message.
		Text = fmt::format("Business {}\n{0F90FA}Name: {FFFFFF}{}\n{0F90FA}Owner: {FFFFFF}{}\n{0F90FA}Fee: {FFFFFF}${}", GetData<int>(BusinessData::kID), GetData<std::string>(BusinessData::kName), GetOwnerID(), GetData<unsigned long long>(BusinessData::kPayout));
	}

	auto Entrance = GetData<Point3D<float>>(BusinessData::kEntrance);
	auto Exit = GetData<Point3D<float>>(BusinessData::kExit);

	SetData<unsigned int>(BusinessData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<unsigned int>(BusinessData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<unsigned int>(BusinessData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

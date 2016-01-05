#include <Business/Business.hpp>

#include <Streamer/MapIcon.hpp>
#include <Streamer/Pickup.hpp>
#include <Streamer/TextLabel.hpp>
#include <Utilities/Utils.hpp>

Business::Business(uint16_t ID, std::shared_ptr<MySQLResult> Result)
{
	// Let's do that because the result vector is from index 0.
	ID--;

	auto Length = static_cast<uint8_t>(BusinessData::kEndMySQL);

	for (uint8_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<BusinessData>(i);
		auto Value = Result->GetRowData(ID, Index);

		switch (Index)
		{
			case BusinessData::kID:
			case BusinessData::kOwnerID:
			{
				SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
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
				auto X = std::stof(Result->GetRowData(ID, i++));
				auto Y = std::stof(Result->GetRowData(ID, i++));
				auto Z = std::stof(Result->GetRowData(ID, i));

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
						SetData<int32_t>(Index, std::stoi(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_LONGLONG:
					{
						SetData<int64_t>(Index, std::stoll(Value));
						break;
					}
					case enum_field_types::MYSQL_TYPE_SHORT:
					{
						SetData<int16_t>(Index, static_cast<int16_t>(std::stoi(Value)));
						break;
					}
					case enum_field_types::MYSQL_TYPE_TINY:
					{
						SetData<int8_t>(Index, static_cast<int8_t>(std::stoi(Value)));
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

const uint16_t Business::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint64_t Business::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

const bool Business::IsLocked() const
{
	return GetData<bool>(BusinessData::kLocked);
}

void Business::Manage()
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

#include <House/CHouse.hpp>

#include <Streamer/Pickup.hpp>
#include <Streamer/MapIcon.hpp>
#include <Streamer/TextLabel.hpp>

#include <Base/CPoint.hpp>
#include <Utilities/Utils.hpp>

CHouse::CHouse(uint16_t ID, std::shared_ptr<CResult> Result)
{
	// Let's do that because the result vector is from index 0.
	ID--;

	auto Length = static_cast<size_t>(HouseData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<HouseData>(i);
		auto Value = Result->GetRowData(ID, Index);

		if (Index == HouseData::kID || Index == HouseData::kOwnerID)
		{
			SetData<uint64_t>(Index, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (Index == HouseData::kEntrance || Index == HouseData::kExit)
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

	auto OwnerID = GetData<uint64_t>(HouseData::kOwnerID);
	auto Position = GetData<Point3D<float>>(HouseData::kEntrance);
	auto Position2 = GetData<Point3D<float>>(HouseData::kExit);

	MapIcon::Create(Point3D<float>(Position.X, Position.Y, Position.Z), 31);
	Pickup::Create(19470, OwnerID == 0 ? 2 : 2, Point3D<float>(Position.X, Position.Y, Position.Z));
	TextLabel::Create(OwnerID == 0 ? "Casa de vanzare!" : "Casa cumparata", 0xFFFFFF, Point3D<float>(Position.X, Position.Y, Position.Z));

	Pickup::Create(1318, OwnerID == 0 ? 23 : 23, Point3D<float>(Position2.X, Position2.Y, Position2.Z));

	TextLabel::Create("Exit" , 0xFFFFFF, Point3D<float>(Position2.X, Position2.Y, Position2.Z));

}

const uint16_t CHouse::GetID() const
{
	return GetData<uint16_t>(HouseData::kID);
}

const uint64_t CHouse::GetOwnerID() const
{
	return GetData<uint64_t>(HouseData::kOwnerID);
}

void CHouse::Manage()
{
	uint16_t MapIconID;
	std::string Text;

	// TODO: Create a function to format the number with comma, eg.: 1000 => 1,000.

	if (GetData<uint64_t>(HouseData::kOwnerID) == 0)
	{
		Text = fmt::format("{FFFFFF}This house is for sale\n{0F90FA}Price: {FFFFFF}${}\n{0F90FA}Level: {FFFFFF}{}\n{0F90FA}to buy this house type /COMMAND_HERE.",
			GetData<uint64_t>(HouseData::kID), GetData<uint64_t>(HouseData::kPrice), GetData<uint64_t>(HouseData::kLevel));

		MapIconID = 31;
	}
	else
	{
		// TODO: Check if the house is locked and set a specific message, also check if it can be rented.
		Text = fmt::format("{FFFFFF}House %i\n{0F90FA}Owner: {FFFFFF}%s\n{0F90FA}Level: {FFFFFF}%i", GetData<uint64_t>(HouseData::kID), GetData<uint64_t>(HouseData::kOwnerID));

		MapIconID = 32;
	}

	auto Entrance = GetData<Point3D<float>>(HouseData::kEntrance);
	auto Exit = GetData<Point3D<float>>(HouseData::kExit);

	SetData<uint32_t>(HouseData::kMapIconID, MapIcon::Create(Entrance, MapIconID));
	SetData<uint32_t>(HouseData::kPickupID, Pickup::Create(1239, 1, Entrance));
	SetData<uint32_t>(HouseData::kTextLabelID, TextLabel::Create(Text, 0x0F90FAFF, Entrance));

	// Create exit pickup.
	Pickup::Create(1239, 1, Exit);
}

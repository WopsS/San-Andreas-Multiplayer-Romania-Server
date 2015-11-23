#include <Business/CBusiness.hpp>

#include <Base/CPoint.hpp>
#include <Utilities/Utils.hpp>

CBusiness::CBusiness(uint16_t aID, std::shared_ptr<CResult> Result)
{	
	auto Length = static_cast<size_t>(BusinessData::kEndMySQL);

	for (size_t i = 0; i < Length; i++)
	{
		auto Index = static_cast<BusinessData>(i);
		auto Value = Result->GetRowData(aID, Index);

		if (i == static_cast<size_t>(BusinessData::kID))
		{
			SetData<uint64_t>(BusinessData::kID, std::stoull(Value));
		}
		else if (i == static_cast<size_t>(BusinessData::kOwnerID))
		{
			SetData<uint64_t>(BusinessData::kOwnerID, Value.length() == 0 ? 0 : std::stoull(Value));
		}
		else if (i == static_cast<float> (BusinessData::kEnterance))
		{
			auto X = std::stof(Result->GetRowData(aID, i++));
			auto Y = std::stof(Result->GetRowData(aID, i++));
			auto Z = std::stof(Result->GetRowData(aID, i));

			SetData<Point3D<float>>(BusinessData::kEnterance, Point3D<float>(X, Y, Z));
		}
		else
		{
			if (Utils::IsNumber(Value) == true)
			{
				SetData<uint32_t>(Index, std::stoul(Value));
			}
			else
			{
				SetData<std::string>(Index, Value);
			}
		}
	}
}

CBusiness::~CBusiness()
{
}

const uint16_t CBusiness::GetID() const
{
	return GetData<uint16_t>(BusinessData::kID);
}

const uint64_t CBusiness::GetOwnerID() const
{
	return GetData<uint64_t>(BusinessData::kOwnerID);
}

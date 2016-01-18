#include <stdafx.hpp>
#include <MySQL/Result.hpp>

std::unique_ptr<MySQLResult> MySQLResult::GetRowResult(size_t Index) const
{
	auto Result = std::make_unique<MySQLResult>();

	if (Index < GetRowCount())
	{
		Result->m_fields = m_fields;
		Result->m_data.push_back(m_data.at(Index));
	}

	return std::move(Result);
}

const FieldInformation MySQLResult::GetField(const std::string& Name) const
{
	if (Name.empty() == false)
	{
		for (size_t i = 0; i < GetFieldCount(); i++)
		{
			auto Field = m_fields.at(i);

			if (Field.Name.compare(Name) == 0)
			{
				return Field;
			}
		}
	}

	return FieldInformation();
}

const std::string MySQLResult::GetRowData(size_t RowIndex, const std::string& FieldName) const
{
	if (RowIndex < GetRowCount() && FieldName.empty() == false)
	{
		for (size_t i = 0; i < GetFieldCount(); i++)
		{
			if (m_fields.at(i).Name.compare(FieldName) == 0)
			{
				return m_data[RowIndex][i];
			}
		}
	}

	return std::string();
}

#include <MySQL/Result.hpp>

const enum_field_types MySQLResult::GetColumnType(const std::string& Name) const
{
	if (Name.empty() == false)
	{
		for (size_t i = 0; i < GetColumnCount(); i++)
		{
			auto Field = m_columns.at(i);

			if (Field.Name.compare(Name) == 0)
			{
				return Field.Type;
			}
		}
	}

	return enum_field_types::MYSQL_TYPE_BIT;
}

const std::string MySQLResult::GetRowData(size_t RowIndex, const std::string& FieldName) const
{
	if (RowIndex < GetRowCount() && FieldName.empty() == false)
	{
		for (size_t i = 0; i < GetColumnCount(); i++)
		{
			if (m_columns.at(i).Name.compare(FieldName) == 0)
			{
				return m_data[RowIndex][i];
			}
		}
	}

	return std::string();
}

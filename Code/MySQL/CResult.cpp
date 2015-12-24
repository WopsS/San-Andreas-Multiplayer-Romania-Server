#include <MySQL/CResult.hpp>

const enum_field_types CResult::GetFieldType(const std::string& Name) const
{
	if (Name.empty() == false)
	{
		for (size_t i = 0; i < m_fieldsCount; i++)
		{
			auto Field = m_fields.at(i);

			if (Field.Name.compare(Name) == 0)
			{
				return Field.Type;
			}
		}
	}

	return enum_field_types::MYSQL_TYPE_BIT;
}

const std::string CResult::GetRowData(size_t RowIndex, const std::string& FieldName) const
{
	if (RowIndex < m_rowsCount && FieldName.empty() == false)
	{
		for (size_t i = 0; i < m_fieldsCount; i++)
		{
			if (m_fields.at(i).Name.compare(FieldName) == 0)
			{
				return m_data[RowIndex][i];
			}
		}
	}

	return std::string();
}

#include <MySQL/CResult.hpp>

std::string CResult::GetRowData(size_t RowIndex, const std::string& FieldName) const
{
	if (RowIndex >= m_rowsCount || FieldName.empty() == true)
	{
		return std::string();
	}

	for (size_t i = 0; i < m_fieldsCount; ++i)
	{
		if (m_fieldsName.at(i).compare(FieldName) == 0)
		{
			return m_data[RowIndex][i];
		}
	}

	return std::string();
}

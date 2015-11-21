#include <MySQL/CResult.hpp>

CResult::CResult()
	: m_data(nullptr)
{
}

CResult::~CResult()
{
	if (m_data != nullptr)
	{
		// Free the memory occupied by our data array, we do that to prevent memory leaking.
		for (size_t i = 0; i < m_rowsCount; i++)
		{
			for (size_t j = 0; j < m_fieldsCount; j++)
			{
				delete[] m_data[i][j];
			}

			delete[] m_data[i];
		}

		delete[] m_data;
	}
}

std::string CResult::GetRowData(size_t RowIndex, const std::string& FieldName) const
{
	if (RowIndex >= m_rowsCount || FieldName.empty() == true)
	{
		return std::string();
	}

	for (size_t i = 0; i != m_fieldsCount; ++i)
	{
		if (m_fieldsName.at(i).compare(FieldName) == 0)
		{
			return m_data[RowIndex][i];
		}
	}

	return std::string();
}

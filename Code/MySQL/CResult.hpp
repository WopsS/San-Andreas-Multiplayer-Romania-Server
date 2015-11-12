#pragma once

#include <string>
#include <vector>

#include <mysql.h>

class CConnection;

class CResult
{
public:

	CResult();
	~CResult();

	inline ULONG GetFieldCount() const
	{
		return m_fieldsCount;
	}

	inline ULONG GetRowCount() const
	{
		return m_rowsCount;
	}

	// TODO: Maybe an enum will be better for this instead the index or name?

	std::string GetRowData(size_t RowIndex, size_t FieldIndex) const;

	std::string GetRowData(size_t RowIndex, const std::string& FieldName) const;

private:

	friend class CConnection;

	char*** m_data;

	ULONG m_affectedRows;

	size_t m_fieldsCount;

	size_t m_insertId;

	ULONG m_rowsCount;

	ULONG m_warningCount;

	std::vector<std::string> m_fieldsName;
};
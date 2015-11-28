#pragma once

#include <string>
#include <vector>

#include <mysql.h>

class CConnection;

class CResult
{
public:

	CResult() = default;
	~CResult() = default;

	inline const ULONG GetAffectedRows() const
	{
		return m_affectedRows;
	}

	inline const ULONG GetFieldCount() const
	{
		return m_fieldsCount;
	}

	inline const my_ulonglong GetInsertedID() const
	{
		return m_insertID;
	}

	inline const ULONG GetRowCount() const
	{
		return m_rowsCount;
	}

	inline const ULONG GetWarningCount() const
	{
		return m_warningCount;
	}

	template<typename T>
	inline std::string GetRowData(const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (Index < m_fieldsCount)
		{
			return m_data[0][Index];
		}

		return std::string();
	}

	template<typename T>
	inline std::string GetRowData(size_t RowIndex, const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (RowIndex < m_rowsCount && Index < m_fieldsCount)
		{
			return m_data[RowIndex][Index];
		}

		return std::string();
	}

	std::string GetRowData(size_t RowIndex, const std::string& FieldName) const;

private:

	friend class CConnection;

	ULONG m_affectedRows;

	size_t m_fieldsCount;

	my_ulonglong m_insertID;

	ULONG m_rowsCount;

	ULONG m_warningCount;

	std::vector<std::string> m_fieldsName;

	std::vector<std::vector<std::string>> m_data;
};
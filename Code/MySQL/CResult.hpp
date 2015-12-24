#pragma once

#include <string>
#include <vector>

#include <mysql.h>

class CConnection;

struct FieldInformation
{
	std::string Name;

	enum_field_types Type;
};

class CResult
{
public:

	CResult() = default;
	~CResult() = default;

	inline const my_ulonglong GetAffectedRows() const
	{
		return m_affectedRows;
	}

	inline const size_t GetFieldCount() const
	{
		return m_fieldsCount;
	}

	inline const my_ulonglong GetInsertedID() const
	{
		return m_insertID;
	}

	inline const my_ulonglong GetRowCount() const
	{
		return m_rowsCount;
	}

	inline const uint32_t GetWarningCount() const
	{
		return m_warningCount;
	}

	template<typename T>
	inline const enum_field_types GetFieldType(const T& Index) const
	{
		auto FieldIndex = static_cast<size_t>(Index);

		if (FieldIndex < m_fieldsCount)
		{
			return m_fields.at(FieldIndex).Type;
		}

		return enum_field_types::MYSQL_TYPE_BIT;
	}

	const enum_field_types GetFieldType(const std::string& Name) const;

	template<typename T>
	inline const std::string GetRowData(const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (Index < m_fieldsCount)
		{
			return m_data[0][Index];
		}

		return std::string();
	}

	template<typename T>
	inline const std::string GetRowData(size_t RowIndex, const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (RowIndex < m_rowsCount && Index < m_fieldsCount)
		{
			return m_data[RowIndex][Index];
		}

		return std::string();
	}

	const std::string GetRowData(size_t RowIndex, const std::string& FieldName) const;

private:

	friend class CConnection;

	my_ulonglong m_affectedRows;

	size_t m_fieldsCount;

	my_ulonglong m_insertID;

	my_ulonglong m_rowsCount;

	uint32_t m_warningCount;

	std::vector<FieldInformation> m_fields;

	std::vector<std::vector<std::string>> m_data;
};
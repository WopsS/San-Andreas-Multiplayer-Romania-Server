#pragma once

struct ColumnInformation
{
	std::string Name;

	enum_field_types Type;
};

class MySQLResult
{
public:

	MySQLResult() = default;
	~MySQLResult() = default;

	inline const my_ulonglong GetAffectedRows() const
	{
		return m_affectedRows;
	}

	inline const size_t GetColumnCount() const
	{
		return m_columns.size();
	}

	inline const my_ulonglong GetInsertedID() const
	{
		return m_insertID;
	}

	inline const my_ulonglong GetRowCount() const
	{
		return m_data.size();
	}

	inline const uint32_t GetWarningCount() const
	{
		return m_warnings;
	}

	template<typename T>
	inline const enum_field_types GetColumnType(const T& Index) const
	{
		auto FieldIndex = static_cast<size_t>(Index);

		if (FieldIndex < GetColumnCount())
		{
			return m_columns.at(FieldIndex).Type;
		}

		return enum_field_types::MYSQL_TYPE_BIT;
	}

	const enum_field_types GetColumnType(const std::string& Name) const;

	template<typename T>
	inline const std::string GetRowData(const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (Index < GetColumnCount())
		{
			return m_data[0][Index];
		}

		return std::string();
	}

	template<typename T>
	inline const std::string GetRowData(size_t RowIndex, const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (RowIndex < GetRowCount() && Index < GetColumnCount())
		{
			return m_data[RowIndex][Index];
		}

		return std::string();
	}

	const std::string GetRowData(size_t RowIndex, const std::string& FieldName) const;

private:

	friend class Connection;

	my_ulonglong m_affectedRows;

	my_ulonglong m_insertID;

	uint32_t m_warnings;

	std::vector<ColumnInformation> m_columns;

	std::vector<std::vector<std::string>> m_data;
};
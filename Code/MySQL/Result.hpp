#pragma once

class MySQLResult
{
public:

	MySQLResult() = default;
	~MySQLResult() = default;

	inline const my_ulonglong GetAffectedRows() const
	{
		return m_affectedRows;
	}

	inline const size_t GetFieldCount() const
	{
		return m_fields.size();
	}

	template<typename T>
	const std::string GetFieldName(const T& Index) const
	{
		auto FieldIndex = static_cast<size_t>(Index);

		if (FieldIndex < GetFieldCount())
		{
			return m_fields.at(FieldIndex).Name;
		}

		return std::string();
	}

	template<typename T>
	inline const FieldInformation GetField(const T& Index) const
	{
		auto FieldIndex = static_cast<size_t>(Index);

		if (FieldIndex < GetFieldCount())
		{
			return m_fields.at(FieldIndex);
		}

		return FieldInformation();
	}

	const FieldInformation GetField(const std::string& Name) const;

	inline const my_ulonglong GetInsertedID() const
	{
		return m_insertID;
	}

	inline const my_ulonglong GetRowCount() const
	{
		return m_data.size();
	}

	std::unique_ptr<MySQLResult> GetRowResult(size_t Index) const;

	inline const unsigned int GetWarningCount() const
	{
		return m_warnings;
	}

	template<typename T>
	inline const std::string GetRowData(const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (Index < GetFieldCount())
		{
			return m_data[0][Index];
		}

		return std::string();
	}

	template<typename T>
	inline const std::string GetRowData(size_t RowIndex, const T& FieldIndex) const
	{
		auto Index = static_cast<size_t>(FieldIndex);

		if (RowIndex < GetRowCount() && Index < GetFieldCount())
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

	unsigned int m_warnings;

	std::vector<FieldInformation> m_fields;

	std::vector<std::vector<std::string>> m_data;
};
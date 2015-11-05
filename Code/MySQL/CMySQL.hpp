#pragma once

#include <CSingleton.hpp>

class CMySQL : public CSingleton<CMySQL>
{
public:

	// TODO: Create functions to add a query and process functions.

private:

	friend class CSingleton<CMySQL>;

	CMySQL();
	~CMySQL();
};
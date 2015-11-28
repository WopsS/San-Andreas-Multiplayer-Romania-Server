#pragma once

#include <memory>

#include <stdafx.hpp>
#include <format.h>
#include <Base/CSingleton.hpp>
#include <MySQL/CMySQL.hpp>

class CServer : public CSingleton<CServer>
{
public:

	void Initialize();

private:

	friend class CSingleton<CServer>;

	CServer() = default;
	~CServer() = default;

	void InitializeBusinesses(std::shared_ptr<CResult> Result);

	void InitializeFactions(std::shared_ptr<CResult> Result);

	void InitializeHouses(std::shared_ptr<CResult> Result);

	void InitializeVehicles(std::shared_ptr<CResult> Result);
};
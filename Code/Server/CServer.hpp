#pragma once

#include <memory>

#include <stdafx.hpp>
#include <format.h>
#include <Base/CSingleton.hpp>
#include <Business/CBusiness.hpp>
#include <Dialog/CDialog.hpp>
#include <House/CHouse.hpp>
#include <MySQL/CMySQL.hpp>
#include <Vehicle/CVehicle.hpp>

class CServer : public CSingleton<CServer>
{
public:

	void Initialize();

private:

	friend class CSingleton<CServer>;

	CServer();
	~CServer();

	void InitializeBusinesses(std::shared_ptr<CResult> Result);

	void InitializeHouses(std::shared_ptr<CResult> Result);

	void InitializeVehicles(std::shared_ptr<CResult> Result);
};
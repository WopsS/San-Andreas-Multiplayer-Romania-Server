#pragma once

#include <Base/CSingleton.hpp>

class CServer : public CSingleton<CServer>
{
public:

	// TODO: Store information about server and maybe load here businesses, houses and vehicles.
	void CreateDialogs();

private:

	friend class CSingleton<CServer>;

	CServer();
	~CServer();
};
#pragma once

#include <Business/Enums.hpp>

class Business : public Map<unsigned short, Business>, private Data<BusinessData>
{
public:

	Business(std::unique_ptr<MySQLResult> Result);
	~Business() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const unsigned short GetID() const;

	const unsigned char GetInterior() const;

	const unsigned char GetLevel() const;

	const std::string GetName() const;

	const unsigned long long GetOwnerID() const;

	const unsigned int GetPayout() const;

	const unsigned int GetPrice() const;

	const BusinessType GetType() const;

	const unsigned int GetVirtualWorld() const;

	const bool IsLocked() const;

private:

	void Manage();
};
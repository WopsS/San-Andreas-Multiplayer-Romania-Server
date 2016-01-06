#pragma once

#include <House/Enums.hpp>

class House : public Map<unsigned short, House>, private Data<HouseData>
{
public:

	House(std::unique_ptr<MySQLResult> Result);
	~House() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const unsigned short GetID() const;

	const unsigned char GetInterior() const;

	const unsigned char GetLevel() const;

	const unsigned long long GetOwnerID() const;

	const unsigned int GetPrice() const;

	const unsigned int GetRentPrice() const;

	const unsigned int GetVirtualWorld() const;

	const bool IsLocked() const;

private:

	void Manage();
};
#pragma once

#include <House/Enums.hpp>

class House : public Map<unsigned short, House>, private Data<HouseData>
{
public:

	House(std::unique_ptr<MySQLResult> Result);
	~House() = default;

	const Point3D<float> GetExit() const;

	const Point3D<float> GetEntrance() const;

	const unsigned short GetID() const;

	const unsigned long long GetOwnerID() const;

	const bool IsLocked() const;

private:

	void Manage();
};
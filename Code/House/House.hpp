#pragma once

#include <House/Enums.hpp>

class House : public Map<uint16_t, House>, private Data<HouseData>
{
public:

	House(std::unique_ptr<MySQLResult> Result);
	~House() = default;

	const Point3D<float> GetExit() const;

	const Point3D<float> GetEntrance() const;

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;

	const bool IsLocked() const;

private:

	void Manage();
};
#pragma once

#include <House/Enums.hpp>

class House : public Map<uint16_t, House>, private Data<HouseData>
{
public:

	House(std::unique_ptr<MySQLResult> Result);
	~House() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const uint16_t GetID() const;

	const uint8_t GetInterior() const;

	const uint8_t GetLevel() const;

	const bool GetLocked() const;

	const uint64_t GetOwnerID() const;

	const uint32_t GetPrice() const;

	const uint32_t GetRentPrice() const;

	const uint32_t GetVirtualWorld() const;

	const bool IsLocked() const;

	const bool IsOwned() const;

	void SetDoors(bool Status);

	void SetOwner(uint64_t ID);

private:

	void Manage();
};
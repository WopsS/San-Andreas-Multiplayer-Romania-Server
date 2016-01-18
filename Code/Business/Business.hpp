#pragma once

#include <Business/Enums.hpp>

class Business : public Map<uint16_t, Business>, private Data<BusinessData>
{
public:

	Business(std::unique_ptr<MySQLResult> Result);
	~Business() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const uint16_t GetID() const;

	const uint8_t GetInterior() const;

	const uint8_t GetLevel() const;

	const std::string GetName() const;

	const uint64_t GetOwnerID() const;

	const uint32_t GetPayout() const;

	const uint32_t GetPrice() const;

	const BusinessType GetType() const;

	const uint32_t GetVirtualWorld() const;

	const bool IsLocked() const;

private:

	void Manage();
};
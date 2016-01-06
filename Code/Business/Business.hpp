#pragma once

#include <Business/Enums.hpp>

class Business : public Map<uint16_t, Business>, private Data<BusinessData>
{
public:

	Business(std::unique_ptr<MySQLResult> Result);
	~Business() = default;

	const Point3D<float> GetExit() const;

	const Point3D<float> GetEntrance() const;

	const uint16_t GetID() const;

	const uint64_t GetOwnerID() const;

	const bool IsLocked() const;

private:

	void Manage();
};
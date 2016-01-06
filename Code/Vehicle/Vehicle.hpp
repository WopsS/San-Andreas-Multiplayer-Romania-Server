#pragma once

#include <Vehicle/Enums.hpp>

class Vehicle : public Map<unsigned short, Vehicle>, private Data<VehicleData>
{
public:

	Vehicle(std::unique_ptr<MySQLResult> Result);
	Vehicle(int Model, const Point3D<float>& Position, float Rotation, int Color1, int Color2, int RespawnTine = -1, bool Siren = false);
	~Vehicle() = default;

	const unsigned short Vehicle::GetGameID() const;

	const unsigned short GetMySQLID() const;

	const unsigned long long GetOwnerID() const;

	const bool GetParameter(VehicleParameters Parameter) const;

	const std::vector<bool> GetParameters() const;

	const bool SetParameter(VehicleParameters Parameter, bool Status) const;
};
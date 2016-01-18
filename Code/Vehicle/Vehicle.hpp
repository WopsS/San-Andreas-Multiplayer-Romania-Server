#pragma once

#include <Vehicle/Enums.hpp>

class Vehicle : public Map<uint16_t, Vehicle>, private Data<VehicleData>
{
public:

	Vehicle(std::unique_ptr<MySQLResult> Result);
	Vehicle(int32_t Model, const Point3D<float>& Position, float Rotation, int32_t Color1, int32_t Color2, int32_t RespawnTine = -1, bool Siren = false);
	~Vehicle() = default;

	const uint8_t GetColor1() const;

	const uint8_t GetColor2() const;

	const uint16_t GetGameID() const;

	const uint16_t GetMySQLID() const;

	const uint64_t GetOwnerID() const;

	const uint16_t GetModel() const;

	const bool GetParameter(VehicleParameters Parameter) const;

	const std::vector<bool> GetParameters() const;

	const Point3D<float> GetPosition() const;

	const uint32_t GetRespawnTine() const;

	const float GetRotation() const;

	const bool HasSiren() const;

	const bool SetParameter(VehicleParameters Parameter, bool Status) const;
};
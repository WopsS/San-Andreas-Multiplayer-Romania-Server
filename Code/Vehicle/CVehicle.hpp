#pragma once

#include <Vehicle/Enums.hpp>

class CVehicle : public CMap<uint16_t, CVehicle>, private CData<VehicleData>
{
public:

	CVehicle(uint16_t aID, std::shared_ptr<CResult> Result);
	CVehicle(int Model, const Point3D<float>& Position, float Rotation, int Color1, int Color2, int RespawnTine = -1, bool Siren = false);
	~CVehicle() = default;

	const uint16_t CVehicle::GetGameID() const;

	const uint16_t GetMySQLID() const;

	const uint64_t GetOwnerID() const;

	const bool GetParameter(VehicleParameters Parameter) const;

	const std::vector<bool> GetParameters() const;

	const bool SetParameter(VehicleParameters Parameter, bool Status) const;
};
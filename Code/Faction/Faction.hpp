#pragma once

#include <Faction/Enums.hpp>

class Faction : public Map<uint16_t, Faction>, private Data<FactionData>
{
public:

	Faction(std::unique_ptr<MySQLResult> Result);
	~Faction() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const uint16_t GetID() const;

	const std::string GetName() const;
};
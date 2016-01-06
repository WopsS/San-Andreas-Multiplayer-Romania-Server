#pragma once

#include <Faction/Enums.hpp>

class Faction : public Map<unsigned short, Faction>, private Data<FactionData>
{
public:

	Faction(std::unique_ptr<MySQLResult> Result);
	~Faction() = default;

	const Point3D<float> GetEntrance() const;

	const Point3D<float> GetExit() const;

	const unsigned short GetID() const;

	const std::string GetName() const;
};
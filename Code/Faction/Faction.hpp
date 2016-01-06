#pragma once

#include <Faction/Enums.hpp>

class Faction : public Map<unsigned short, Faction>, private Data<FactionData>
{
public:

	Faction(std::unique_ptr<MySQLResult> Result);
	~Faction() = default;

	const std::string GetName() const;
};
#pragma once

#include <Faction/Enums.hpp>

class Faction : public Map<uint16_t, Faction>, private Data<FactionData>
{
public:

	Faction(uint16_t ID, std::shared_ptr<MySQLResult> Result);
	~Faction() = default;

	const std::string GetName() const;
};
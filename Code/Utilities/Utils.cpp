#include "Utils.hpp"

bool Utils::IsNumber(const std::string & Text)
{
	for (size_t i = 0; i < Text.length(); i++)
	{
		if (std::isdigit(Text[i]) == false)
		{
			return false;
		}
	}

	return true;
}

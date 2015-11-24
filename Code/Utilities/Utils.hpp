#pragma once

#include <cctype>
#include <cstdint>
#include <string>

namespace Utils
{
	const bool IsFloat(const std::string& Text);

	const bool IsInteger(const std::string& Text);

	const std::string ToLower(const std::string& Text);
}
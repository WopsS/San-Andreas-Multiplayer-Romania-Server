#pragma once

#include <stdafx.hpp>

struct FieldInformation
{
	std::string Name;

	enum_field_types Type;

	bool IsBool;

	bool IsNumeric;

	bool IsUnsigned;
};
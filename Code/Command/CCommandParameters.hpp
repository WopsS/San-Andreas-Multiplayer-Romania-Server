#pragma once

#include <string>

#include <Base/CData.hpp>

/// <summary>
/// Class which store all parameters for a command.
/// </summary>
/// <remarks>
/// A formatter can be:
///		f - for float.
///		i - for integer.
///		s - for string.
/// </remarks>
class CCommandParameters : public CData<size_t>
{
public:

	CCommandParameters(const std::string& Format, std::string& Parameters);
	~CCommandParameters();

	bool Valid();

private:

	size_t m_requiredParameters;
};
#pragma once

#include <string>

#include <Base/CData.hpp>

/// <summary>
/// Class which store all parameters for a command.
/// </summary>
/// <remarks>
/// A specifier can be:
///		f - for float.
///		i - for integer.
///		p - for player.
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
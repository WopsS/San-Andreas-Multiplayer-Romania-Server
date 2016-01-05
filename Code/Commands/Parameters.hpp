#pragma once

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
class CommandParameters : private Data<size_t>
{
public:

	CommandParameters(const std::string& Format, std::string& Parameters);
	~CommandParameters() = default;

	template<typename T>
	const T GetAt(size_t Index) const
	{
		return GetData<T>(Index);
	}

	bool Valid();

private:

	size_t m_requiredParameters;
};
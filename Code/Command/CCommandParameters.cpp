#include <Command/CCommandParameters.hpp>
#include <Utilities/Utils.hpp>

CCommandParameters::CCommandParameters(const std::string& Format, std::string& Parameters)
	: m_requiredParameters(Format.length())
{
	// If format is empty, so the function doesn't use parameters.
	if (Format.length() > 0 && Parameters.length() > 0)
	{
		for (size_t i = 0; i < m_requiredParameters; i++)
		{
			if (Parameters.length() == 0)
			{
				break;
			}

			auto Position = Parameters.find(' ');
			Position = Position == std::string::npos || i == m_requiredParameters - 1 ? Parameters.length() : Position;

			auto Result = Parameters.substr(0, Position);

			// Check if we have a space after our 'Result', if we have it, delete it.
			Parameters.erase(0, Position == Parameters.length() ? Position : Position + 1);

			switch (Format[i])
			{
				case 's':
				{
					// Check if there is only a string formatter or the string formatter is the last one, if it is append text to result.
					if (i == m_requiredParameters - 1)
					{
						Result = Result + " " + Parameters;
						Parameters.clear();
					}

					SetData<std::string>(i, Result);
					break;
				}
				case 'i':
				{
					if (Utils::IsInteger(Result) == true)
					{
						SetData<int>(i, std::stoi(Result));
					}

					break;
				}
				case 'f':
				{
					if (Utils::IsFloat(Result) == true)
					{
						SetData<float>(i, std::stof(Result));
					}

					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
}

CCommandParameters::~CCommandParameters()
{
}

bool CCommandParameters::Valid()
{
	return m_requiredParameters == GetSize();
}

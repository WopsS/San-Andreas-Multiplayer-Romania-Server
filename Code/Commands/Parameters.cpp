#include <Commands/Parameters.hpp>
#include <Player/Player.hpp>

CommandParameters::CommandParameters(const std::string& Format, std::string& Parameters)
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
				case 'f':
				{
					if (Utils::IsFloat(Result) == true)
					{
						SetData<float>(i, std::stof(Result));
					}

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
				case 'p':
				{
					// Set the player as not found by default.
					SetData<std::shared_ptr<Player>>(i, nullptr);

					// Check if the parameter is a integer, if it is then it is the ID, if not, check for the name in players list.
					if (Utils::IsInteger(Result) == true)
					{
						SetData<std::shared_ptr<Player>>(i, Player::Get(std::stoi(Result)));
					}
					else
					{
						for(auto& Players : Player::GetList())
						{
							if (Players.second->GetName().find(Result) != std::string::npos)
							{
								SetData<std::shared_ptr<Player>>(i, Players.second);

								break;
							}
						}
					}

					break;
				}
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
				default:
				{
					break;
				}
			}
		}
	}
}

bool CommandParameters::Valid()
{
	return m_requiredParameters == GetSize();
}

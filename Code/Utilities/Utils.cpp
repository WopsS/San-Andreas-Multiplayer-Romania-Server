#include <stdafx.hpp>
#include <Utilities/Utils.hpp>

const bool Utils::IsFloat(const std::string& Text)
{
	float Number;

	std::istringstream Stream(Text);
	Stream >> std::noskipws >> Number;

	return Stream.eof() && (Stream.fail() == false);
}

const bool Utils::IsInteger(const std::string& Text)
{
	if (Text.length() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < Text.length(); i++)
	{
		if (std::isdigit(Text[i]) == false)
		{
			return false;
		}
	}

	return true;
}

const std::string Utils::ToLower(const std::string& Text)
{
	auto Result = Text;
	std::transform(Result.begin(), Result.end(), Result.begin(), tolower);

	return Result;
}

const std::string Utils::ToUpper(const std::string& Text)
{
	auto Result = Text;
	std::transform(Result.begin(), Result.end(), Result.begin(), toupper);

	return Result;
}

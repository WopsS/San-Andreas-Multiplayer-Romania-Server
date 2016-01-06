#pragma once

namespace Utils
{
	class numpunct : public std::numpunct<char>
	{
	protected:
		virtual char do_thousands_sep() const 
		{ 
			return ','; 
		}

		virtual std::string do_grouping() const 
		{ 
			return "\03"; 
		}
	};

	template<typename T>
	inline const std::string FormatNumber(T Value)
	{
		std::stringstream Result;

		Result.imbue({ std::locale(), new numpunct });
		Result << std::setprecision(2) << std::fixed << Value;

		return Result.str();

	}

	const bool IsFloat(const std::string& Text);

	const bool IsInteger(const std::string& Text);

	const std::string ToLower(const std::string& Text);

	const std::string ToUpper(const std::string& Text);
}
#include <Utilities/Time.hpp>

const std::tm* Time::GetTM()
{
	auto timeNow = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(timeNow);

	return std::localtime(&time_t);
}

std::string Time::GetHour()
{
	std::stringstream stream;
	stream << std::put_time(GetTM(), "%H");

	return stream.str();
}

std::string Time::GetMinutes()
{
	std::stringstream stream;
	stream << std::put_time(GetTM(), "%M");

	return stream.str();
}

std::string Time::GetSeconds()
{
	std::stringstream stream;
	stream << std::put_time(GetTM(), "%S");

	return stream.str();
}

std::string Time::GetYear()
{
	std::stringstream stream;
	stream << std::put_time(GetTM(), "%Y");

	return stream.str();
}

std::string Time::GetTime()
{
	std::stringstream stream;
	stream << std::put_time(GetTM(), "%X");

	return stream.str();
}

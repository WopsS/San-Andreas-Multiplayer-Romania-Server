#include <Utilities/Time.hpp>

std::string Time::GetHour()
{
	auto timeNow = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(timeNow);

	std::stringstream stream;
	stream << std::put_time(std::localtime(&time_t), "%H");

	return stream.str();
}

std::string Time::GetTime()
{
	auto timeNow = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(timeNow);

	std::stringstream stream;
	stream << std::put_time(std::localtime(&time_t), "%X");

	return stream.str();
}

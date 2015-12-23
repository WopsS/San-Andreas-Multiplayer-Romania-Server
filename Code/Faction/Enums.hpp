#pragma once

enum class FactionData : uint8_t
{
	kID = 0,
	kName,
	kEnterance,
	kExit = kEnterance + 3,

	kEndMySQL, // Used to know the last value in the iteration when MySQL information is loaded.
};
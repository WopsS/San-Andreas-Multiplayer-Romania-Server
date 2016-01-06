#pragma once

enum class FactionData : unsigned char
{
	kID = 0,
	kName,
	kEntrance,
	kExit = kEntrance + 3
};
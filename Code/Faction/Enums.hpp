#pragma once

enum class FactionData : unsigned char
{
	kID = 0,
	kName,
	kEnterance,
	kExit = kEnterance + 3
};
#pragma once

enum class FactionData : uint8_t
{
	kID = 0,
	kName,
	kEnterance,
	kExit = kEnterance + 3
};
#pragma once

enum class CommandFlags : uint8_t
{
	kPlayer = 1 << 0,
	kMember = 1 << 1,
	kSubleader = 1 << 2,
	kLeader = 1 << 3,
	kAdmin = 1 << 4
};

inline int operator&(CommandFlags FirstFlag, int SecondFlag)
{
	return static_cast<int>(FirstFlag) & SecondFlag;
}

inline int operator&(int FirstFlag, CommandFlags SecondFlag)
{
	return FirstFlag & static_cast<int>(SecondFlag);
}

inline int operator&(CommandFlags FirstFlag, CommandFlags SecondFlag)
{
	return static_cast<int>(FirstFlag) & static_cast<int>(SecondFlag);
}

inline int operator|(CommandFlags FirstFlag, CommandFlags SecondFlag)
{
	return static_cast<int>(FirstFlag) | static_cast<int>(SecondFlag);
}
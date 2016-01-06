#pragma once

enum class CommandFlags : unsigned char
{
	kPlayer = 1 << 0,
	kMember = 1 << 1,
	kSubleader = 1 << 2,
	kLeader = 1 << 3,
	kAdmin = 1 << 4
};

inline unsigned int operator&(CommandFlags FirstFlag, unsigned int SecondFlag)
{
	return static_cast<unsigned char>(FirstFlag) & SecondFlag;
}

inline unsigned int operator&(unsigned int FirstFlag, CommandFlags SecondFlag)
{
	return FirstFlag & static_cast<unsigned char>(SecondFlag);
}

inline unsigned int operator&(CommandFlags FirstFlag, CommandFlags SecondFlag)
{
	return static_cast<unsigned char>(FirstFlag) & static_cast<unsigned char>(SecondFlag);
}

inline unsigned int operator|(CommandFlags FirstFlag, CommandFlags SecondFlag)
{
	return static_cast<unsigned char>(FirstFlag) | static_cast<unsigned char>(SecondFlag);
}
#pragma once

enum class PermissionFlags : uint8_t
{
	kPlayer = 1 << 0,
	kMember = 1 << 1,
	kSubleader = 1 << 2,
	kLeader = 1 << 3,
	kAdmin = 1 << 4
};

inline uint32_t operator&(PermissionFlags FirstFlag, uint32_t SecondFlag)
{
	return static_cast<uint8_t>(FirstFlag) & SecondFlag;
}

inline uint32_t operator&(uint32_t FirstFlag, PermissionFlags SecondFlag)
{
	return FirstFlag & static_cast<uint8_t>(SecondFlag);
}

inline uint32_t operator&(PermissionFlags FirstFlag, PermissionFlags SecondFlag)
{
	return static_cast<uint8_t>(FirstFlag) & static_cast<uint8_t>(SecondFlag);
}

inline uint32_t operator|(PermissionFlags FirstFlag, PermissionFlags SecondFlag)
{
	return static_cast<uint8_t>(FirstFlag) | static_cast<uint8_t>(SecondFlag);
}
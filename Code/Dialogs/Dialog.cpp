#include <stdafx.hpp>
#include <Player/Player.hpp>
#include <Dialogs/Dialog.hpp>

Dialog::Dialog()
	: m_buttons{ "", "Close" }
{
}

bool Dialog::CheckAccess(std::shared_ptr<Player> Player)
{
	/*
	* Note:
	* 	We don't use an 'if' for 'HasCustomAccess' because if we have a function which check if the player is part of a faction, the command need know if
	* 	the command is for faction's leader or for members without write anything more in the function.
	*/

	if (m_accessLevel & PermissionFlags::kPlayer && CustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & PermissionFlags::kMember) && Player->IsInAnyFaction() == true && CustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & PermissionFlags::kSubleader) && Player->IsSubleader() == true && CustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & PermissionFlags::kLeader) && Player->IsLeader() == true && CustomAccess(Player) == true)
	{
		return true;
	}
	else if ((m_accessLevel & PermissionFlags::kAdmin) && Player->IsAdmin() == true && CustomAccess(Player) == true)
	{
		return true;
	}

	return false;
}

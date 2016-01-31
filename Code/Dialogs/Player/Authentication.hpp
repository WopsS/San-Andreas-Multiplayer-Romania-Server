#pragma once

#include <Dialogs/Dialog.hpp>

class AuthenticationDialog : public Dialog
{
public:

	AuthenticationDialog();
	~AuthenticationDialog() = default;

	const bool CustomAccess(std::shared_ptr<Player> Player) const;

	void Execute(std::shared_ptr<Player> Player, const DialogResponse& Response, const size_t ItemIndex, const std::string& Text);
};
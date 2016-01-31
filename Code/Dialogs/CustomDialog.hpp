#pragma once

#include <Dialogs/Dialog.hpp>

class CustomDialog : public Dialog
{
public:

	CustomDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string Buttons[2]);
	~CustomDialog() = default;

	const bool CustomAccess(std::shared_ptr<Player> Player) const 
	{ 
		return true;
	}

	void Execute(std::shared_ptr<Player> Player, const DialogResponse& Response, const size_t ItemIndex, const std::string& Text) { }
};
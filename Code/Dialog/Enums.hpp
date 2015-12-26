#pragma once

#include <cstdint>

enum class DialogData : uint8_t
{
	kID = 0,
	kStyle,
	kCaption,
	kText,
	kButton1,
	kButton2
};

enum class DialogStyle : uint8_t
{
	kMessage = 0, // DIALOG_STYLE_MSGBOX
	kInput, // DIALOG_STYLE_INPUT
	kList, // DIALOG_STYLE_LIST
	kPassword, // DIALOG_STYLE_PASSWORD
	kTabList, // DIALOG_STYLE_TABLIST
	kTabListHeaders // DIALOG_STYLE_TABLIST_HEADERS
};

enum class DialogResponse : uint16_t
{
	kRight = 0, // Used to close the dialog or cancel the current action.
	kLeft // Used to select an item from the list, go to the next step of the dialog, etc..
};

enum class DialogID : uint16_t
{
	kRegister = 1,
	kRegisterConfirmation,
	kEmail,
	kPin,
	kPinConfirmation,
	kSex,
	kCompleteRegistration,
	kTutorial,

	kAuthentication
};

#include <stdafx.hpp>
#include <Dialogs/CustomDialog.hpp>

CustomDialog::CustomDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string Buttons[2])
{
	m_id = ID;
	m_style = Style;
	m_caption = Caption;
	m_text = Text;
	m_buttons[0] = Buttons[0];
	m_buttons[1] = Buttons[1];
}
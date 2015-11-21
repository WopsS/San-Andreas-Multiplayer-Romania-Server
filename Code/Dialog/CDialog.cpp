#include <Dialog/CDialog.hpp>

CDialog::CDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2)
	: m_id(ID)
	, m_style(Style)
	, m_caption(Caption)
	, m_text(Text)
	, m_button1(Button1)
	, m_button2(Button2)
{
}

CDialog::~CDialog()
{
}
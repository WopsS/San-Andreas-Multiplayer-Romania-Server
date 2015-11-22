#include <Dialog/CDialog.hpp>

CDialog::CDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2)
{
	SetData<DialogID>(DialogData::kID, ID);
	SetData<DialogStyle>(DialogData::kStyle, Style);
	SetData<std::string>(DialogData::kCaption, Caption);
	SetData<std::string>(DialogData::kText, Text);
	SetData<std::string>(DialogData::kButton1, Button1);
	SetData<std::string>(DialogData::kButton2, Button2);
}

CDialog::~CDialog()
{
}

const DialogID CDialog::GetID() const
{
	return GetData<DialogID>(DialogData::kID);
}

const DialogStyle CDialog::GetStyle() const
{
	return GetData<DialogStyle>(DialogData::kStyle);
}

const std::string CDialog::GetCaption() const
{
	return GetData<std::string>(DialogData::kCaption);
}

const std::string CDialog::GetText() const
{
	return GetData<std::string>(DialogData::kText);
}

const std::string CDialog::GetButton1() const
{
	return GetData<std::string>(DialogData::kButton1);
}

const std::string CDialog::GetButton2() const
{
	return GetData<std::string>(DialogData::kButton2);
}

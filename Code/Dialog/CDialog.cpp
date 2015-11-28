#include <Dialog/CDialog.hpp>

CDialog::CDialog(dialogfunction_t Function)
	: m_function(Function)
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

const dialogfunction_t CDialog::GetFunction() const
{
	return m_function;
}

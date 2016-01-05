#include <Dialog/Dialog.hpp>

Dialog::Dialog(dialogfunction_t Function)
	: m_function(Function)
{
}

const DialogID Dialog::GetID() const
{
	return GetData<DialogID>(DialogData::kID);
}

const DialogStyle Dialog::GetStyle() const
{
	return GetData<DialogStyle>(DialogData::kStyle);
}

const std::string Dialog::GetCaption() const
{
	return GetData<std::string>(DialogData::kCaption);
}

const std::string Dialog::GetText() const
{
	return GetData<std::string>(DialogData::kText);
}

const std::string Dialog::GetButton1() const
{
	return GetData<std::string>(DialogData::kButton1);
}

const std::string Dialog::GetButton2() const
{
	return GetData<std::string>(DialogData::kButton2);
}

const dialogfunction_t Dialog::GetFunction() const
{
	return m_function;
}

#pragma once

#include <Dialog/Enums.hpp>

class Dialog : public Data<DialogData>
{
public:

	Dialog(dialogfunction_t Function);
	~Dialog() = default;

	const DialogID GetID() const;

	const DialogStyle GetStyle() const;

	const std::string GetCaption() const;

	const std::string GetText() const;

	const std::string GetButton1() const;

	const std::string GetButton2() const;

	const dialogfunction_t GetFunction() const;

private:

	friend class Dialogs;

	dialogfunction_t m_function;
};
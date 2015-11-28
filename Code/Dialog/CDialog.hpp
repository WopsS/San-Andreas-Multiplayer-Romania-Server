#pragma once

#include <functional>
#include <string>

#include <Base/CData.hpp>
#include <Base/Types.hpp>
#include <Dialog/Enums.hpp>

class CDialog : public CData<DialogData>
{
public:

	CDialog(dialogfunction_t Function);
	~CDialog() = default;

	const DialogID GetID() const;

	const DialogStyle GetStyle() const;

	const std::string GetCaption() const;

	const std::string GetText() const;

	const std::string GetButton1() const;

	const std::string GetButton2() const;

	const dialogfunction_t GetFunction() const;

private:

	friend class CDialogs;

	dialogfunction_t m_function;
};
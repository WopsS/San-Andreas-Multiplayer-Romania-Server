#pragma once

#include <string>

#include <Base/CMap.hpp>
#include <Base/CData.hpp>
#include <Dialog/Enums.hpp>

class CDialog : public CMap<DialogID, CDialog>, private CData<DialogData>
{
public:

	CDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2);
	~CDialog();

	const DialogID GetID() const;

	const DialogStyle GetStyle() const;

	const std::string GetCaption() const;

	const std::string GetText() const;

	const std::string GetButton1() const;

	const std::string GetButton2() const;
};
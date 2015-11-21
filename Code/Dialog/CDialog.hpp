#pragma once

#include <string>

#include <Base/CMap.hpp>
#include <Dialog/Enums.hpp>

class CDialog : public CMap<DialogID, CDialog>
{
public:

	CDialog(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2);
	~CDialog();

	inline const DialogID& GetID() const
	{
		return m_id;
	}

	inline const DialogStyle& GetStyle() const
	{
		return m_style;
	}

	inline const std::string& GetCaption() const
	{
		return m_caption;
	}

	inline const std::string& GetText() const
	{
		return m_text;
	}

	inline const std::string& GetButton1() const
	{
		return m_button1;
	}

	inline const std::string& GetButton2() const
	{
		return m_button2;
	}

private:

	friend class CMap<DialogID, CDialog>;

	DialogID m_id;

	DialogStyle m_style;

	std::string m_caption;

	std::string m_text;

	std::string m_button1;

	std::string m_button2;
};
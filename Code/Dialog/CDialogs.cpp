#include <Dialog/CDialogs.hpp>

#include <random>
#include <regex>

#include <MySQL/CMySQL.hpp>
#include <Utilities/Encryption.hpp>
#include <Utilities/Utils.hpp>

CDialogs::CDialogs()
{
	Add(DialogID::kRegister, DialogStyle::kPassword, "Registration",
		"Hello {{95A3FF}}{}{{BECBFC}},\n\nYou don't have an account, you need to register in order to play on this server.\nPassword must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 32{{BECBFC}} characters.\n\nPlease type your password below:",
		"Next", "Cancel", Bind(&CDialogs::Register, this));

	Add(DialogID::kRegisterConfirmation, DialogStyle::kPassword, "Registration - Password confirmation",
		"{{95A3FF}}{}{{BECBFC}}, you need to confirm your password to make sure it is the correct one.\n\nPlease type your password below:", "Next", "Back", Bind(&CDialogs::RegisterConfirmation, this));

	Add(DialogID::kEmail, DialogStyle::kInput, "Registration - Email",
		"{{95A3FF}}{}{{BECBFC}}, we need your email because when you forgot your {{95A3FF}}password{{BECBFC}} or your {{95A3FF}}PIN{{BECBFC}} number we will send a new one to you.\n\nPlease type your email below:",
		"Next", "Back", Bind(&CDialogs::Email, this));

	Add(DialogID::kPin, DialogStyle::kInput, "Registration - Pin",
		"Thank you {{95A3FF}}{}{{BECBFC}}, your email is {{95A3FF}}{}{{BECBFC}}.\n\nNow you need to enter a {{95A3FF}}PIN number{{BECBFC}} to add a second protection to your account.\nPIN number will be used to {{9E0028}}unlock access{{BECBFC}} for few commands (change password, transfer money, give money to player, etc.).\n\nPin must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 8{{BECBFC}} digits.",
		"Next", "Back", Bind(&CDialogs::Pin, this));

	Add(DialogID::kPinConfirmation, DialogStyle::kMessage, "Registration - Pin confirmation",
		"We need to be sure about your {{95A3FF}}PIN number{{BECBFC}}.\nCurrent PIN number is {{9E0028}}{}{{BECBFC}}, is that correct?", "Yes", "No", Bind(&CDialogs::PinConfirmation, this));

	Add(DialogID::kSex, DialogStyle::kMessage, "Registration - Sex",
		"Thank you {{95A3FF}}{}{{BECBFC}}.\n\nNow please select your sex, are you a {{95A3FF}}male{{BECBFC}} or a {{95A3FF}}female{{BECBFC}}?", "Male", "Female", Bind(&CDialogs::Sex, this));

	Add(DialogID::kCompleteRegistration, DialogStyle::kMessage, "Registration - Confirmation",
		"Thank you {{95A3FF}}{}{{BECBFC}} for the information. Your character will be for {{95A3FF}}{}{{BECBFC}}.\n\nThis is the last step of the registration, please confirm if you want to finish your registration or to cancel it.",
		"Finish", "Cancel", Bind(&CDialogs::CompleteRegistration, this));

	Add(DialogID::kTutorial, DialogStyle::kMessage, "Tutorial", "Hello {{95A3FF}}{}{{BECBFC}}, do you want to follow our tutorial?\n\nIt will show you few things on this server.", "Yes", "No", 
		Bind(&CDialogs::Tutorial, this));

	Add(DialogID::kAuthentication, DialogStyle::kPassword, "Authentication", "Hello {{95A3FF}}{}{{BECBFC}},\n\nYou have an account on our server, please login to access it.", "Login", "Cancel", 
		Bind(&CDialogs::Authentication, this));
}

CDialogs::~CDialogs()
{
}

void CDialogs::Add(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2, dialogfunction_t Function)
{
	auto Dialog = std::make_shared<CDialog>(Function);

	Dialog->SetData<DialogID>(DialogData::kID, ID);
	Dialog->SetData<DialogStyle>(DialogData::kStyle, Style);
	Dialog->SetData<std::string>(DialogData::kCaption, Caption);
	Dialog->SetData<std::string>(DialogData::kText, Text);
	Dialog->SetData<std::string>(DialogData::kButton1, Button1);
	Dialog->SetData<std::string>(DialogData::kButton2, Button2);

	m_dialogs.emplace(ID, std::move(Dialog));
}

CDialog CDialogs::Create(const DialogID& ID, const std::string& Text)
{
	auto Dialog = Get(ID);

	return Create(ID, Dialog->GetStyle(), Dialog->GetCaption(), Text, Dialog->GetButton1(), Dialog->GetButton2(), Dialog->GetFunction());
}

CDialog CDialogs::Create(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2, dialogfunction_t Function)
{
	CDialog Result(Function);

	Result.SetData<DialogID>(DialogData::kID, ID);
	Result.SetData<DialogStyle>(DialogData::kStyle, Style);
	Result.SetData<std::string>(DialogData::kCaption, Caption);
	Result.SetData<std::string>(DialogData::kText, Text);
	Result.SetData<std::string>(DialogData::kButton1, Button1);
	Result.SetData<std::string>(DialogData::kButton2, Button2);

	return Result;
}

bool CDialogs::Execute(std::shared_ptr<CPlayer> Player, const DialogID& ID, const DialogResponse& Response, const size_t ItemIndex, const std::string& Text)
{
	if (m_dialogs.find(ID) == m_dialogs.end())
	{
		return false;
	}

	auto Dialog = m_dialogs.at(ID);

	if (Dialog->GetFunction() != nullptr)
	{
		// Rebind function with the new parameters.
		auto Function = std::bind(Dialog->GetFunction(), Player, Response, ItemIndex, Text);

		// Call the function.
		Function();
	}

	return true;
}

const std::shared_ptr<CDialog> CDialogs::Get(const DialogID& ID) const
{
	if (m_dialogs.find(ID) == m_dialogs.end())
	{
		return std::make_shared<CDialog>(dialogfunction_t());
	}

	return m_dialogs.at(ID);
}

void CDialogs::Authentication(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->Kick();
	}
	else
	{
		auto Password = Encryption::Encrypt(Text, Player->GetSalt());

		// TODO: Insert fail authentication log or success log.

		if (Player->GetData<std::string>(PlayerData::kPassword).compare(Password) == 0)
		{
			Player->SetData<bool>(PlayerData::kAuthenticated, true);
			Player->Spawn();
		}
		else
		{
			Player->ShowDialog(Create(DialogID::kAuthentication,
				"Sorry {{95A3FF}}{}{{BECBFC}} but password which you entered {{9E0028}}doesn't match{{BECBFC}} with your account's password. Please try again.\n\nPlease type your password below:"), Player->GetName());
		}
	}
}

void CDialogs::CompleteRegistration(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->Kick();
	}
	else
	{
		Player->SetData<bool>(PlayerData::kAuthenticated, true);

		CMySQL::GetInstance()->Query(QueryType::kNormal, "INSERT INTO `players` (`Name`, `Password`, `Salt`, `Email`, `Pin`, `Sex`) VALUES (':name', ':password', ':salt', ':email', ':pin', ':sex')",
		{
			CMySQL::GetInstance()->MakeParameter("name", Player->GetName()),
			CMySQL::GetInstance()->MakeParameter("password", Player->GetData<std::string>(PlayerData::kPassword)),
			CMySQL::GetInstance()->MakeParameter("salt", Player->GetSalt()),
			CMySQL::GetInstance()->MakeParameter("email", Player->GetEmail()),
			CMySQL::GetInstance()->MakeParameter("pin", Player->GetData<std::string>(PlayerData::kPin)),
			CMySQL::GetInstance()->MakeParameter("sex", static_cast<uint16_t>(Player->GetSex()))
		}, &CPlayer::OnInserted, Player);

		Player->ShowDialog(DialogID::kTutorial, Player->GetName());
	}
}

void CDialogs::Email(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->ShowDialog(DialogID::kRegister, Player->GetName());
	}
	else
	{
		std::regex Regex("^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");

		// Check if the email is valid.
		if (std::regex_search(Text, Regex))
		{
			Player->SetData<std::string>(PlayerData::kEmail, Text);
			Player->ShowDialog(DialogID::kPin, Player->GetName(), Player->GetEmail());
		}
		else
		{
			Player->ShowDialog(DialogID::kEmail, Player->GetName());
		}
	}
}

void CDialogs::Pin(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->ShowDialog(DialogID::kEmail, Player->GetName());
	}
	else
	{
		if (Text.length() < 4 || Text.length() > 8 || Utils::IsInteger(Text) == false)
		{
			Player->ShowDialog(DialogID::kPin, Player->GetName(), Player->GetEmail());
		}
		else
		{
			Player->SetData<std::string>(PlayerData::kPin, Encryption::Encrypt(Text, Player->GetSalt()));
			Player->ShowDialog(DialogID::kPinConfirmation, Text);
		}
	}
}

void CDialogs::PinConfirmation(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->ShowDialog(DialogID::kPin, Player->GetName(), Player->GetEmail());
	}
	else
	{
		Player->ShowDialog(DialogID::kSex, Player->GetName());
	}
}

void CDialogs::Register(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	// If player press 'Cancel' button let's kick him.
	if (Response == DialogResponse::kRight)
	{
		Player->Kick();
	}
	else
	{
		if (Text.length() < 4 || Text.length() > 32)
		{
			Player->ShowDialog(DialogID::kRegister, Player->GetName());
		}
		else
		{
			// Generate salt for the user and encrypt the password.
			std::random_device RandomDevice;
			std::default_random_engine RandomEngine(RandomDevice());
			std::uniform_int_distribution<int> uniform_dist(12, 32);

			Player->SetData<std::string>(PlayerData::kSalt, Encryption::GenerateSalt(64 + uniform_dist(RandomEngine)));
			Player->SetData<std::string>(PlayerData::kPassword, Encryption::Encrypt(Text, Player->GetSalt()));

			Player->ShowDialog(DialogID::kRegisterConfirmation, Player->GetName());
		}
	}
}

void CDialogs::RegisterConfirmation(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->ShowDialog(DialogID::kRegister, Player->GetName());
	}
	else
	{
		auto Password = Encryption::Encrypt(Text, Player->GetSalt());

		if (Player->GetData<std::string>(PlayerData::kPassword).compare(Password) == 0)
		{
			Player->ShowDialog(DialogID::kEmail, Player->GetName());
		}
		else
		{
			Player->ShowDialog(Create(DialogID::kRegisterConfirmation, 
				"Sorry {{95A3FF}}{}{{BECBFC}} but your confirmation password {{9E0028}}doesn't match{{BECBFC}} with your password. Please try again.\n\nPlease type your password below:"), Player->GetName());
		}
	}
}

void CDialogs::Sex(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	Player->SetData<PlayerSex>(PlayerData::kSex, Response == DialogResponse::kRight ? PlayerSex::kFemale : PlayerSex::kMale);
	Player->ShowDialog(DialogID::kCompleteRegistration, Player->GetName(), Player->GetSex() == PlayerSex::kMale ? "male" : "female");
}

void CDialogs::Tutorial(std::shared_ptr<CPlayer> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	// TODO: Spawn player if he press 'No' or put him in tutorial if he press 'Yes'.

	if (Response == DialogResponse::kRight)
	{
		Player->Spawn();
	}
	else
	{
		Player->Spawn();
	}
}
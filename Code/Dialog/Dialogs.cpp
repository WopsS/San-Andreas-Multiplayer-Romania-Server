#include <Dialog/Dialogs.hpp>

Dialogs::Dialogs()
{
	Add(DialogID::kRegister, DialogStyle::kPassword, "Registration",
		"Hello {{95A3FF}}{}{{BECBFC}},\n\nYou don't have an account, you need to register in order to play on this server.\nPassword must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 32{{BECBFC}} characters.\n\nPlease type your password below:",
		"Next", "Cancel", Bind(&Dialogs::Register, this));

	Add(DialogID::kRegisterConfirmation, DialogStyle::kPassword, "Registration - Password confirmation",
		"{{95A3FF}}{}{{BECBFC}}, you need to confirm your password to make sure it is the correct one.\n\nPlease type your password below:", "Next", "Back", Bind(&Dialogs::RegisterConfirmation, this));

	Add(DialogID::kEmail, DialogStyle::kInput, "Registration - Email",
		"{{95A3FF}}{}{{BECBFC}}, we need your email because when you forgot your {{95A3FF}}password{{BECBFC}} or your {{95A3FF}}PIN{{BECBFC}} number we will send a new one to you.\n\nPlease type your email below:",
		"Next", "Back", Bind(&Dialogs::Email, this));

	Add(DialogID::kPin, DialogStyle::kInput, "Registration - Pin",
		"Thank you {{95A3FF}}{}{{BECBFC}}, your email is {{95A3FF}}{}{{BECBFC}}.\n\nNow you need to enter a {{95A3FF}}PIN number{{BECBFC}} to add a second protection to your account.\nPIN number will be used to {{9E0028}}unlock access{{BECBFC}} for few commands (change password, transfer money, give money to player, etc.).\n\nPin must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 8{{BECBFC}} digits.",
		"Next", "Back", Bind(&Dialogs::Pin, this));

	Add(DialogID::kPinConfirmation, DialogStyle::kMessage, "Registration - Pin confirmation",
		"We need to be sure about your {{95A3FF}}PIN number{{BECBFC}}.\nCurrent PIN number is {{9E0028}}{}{{BECBFC}}, is that correct?", "Yes", "No", Bind(&Dialogs::PinConfirmation, this));

	Add(DialogID::kSex, DialogStyle::kMessage, "Registration - Sex",
		"Thank you {{95A3FF}}{}{{BECBFC}}.\n\nNow please select your sex, are you a {{95A3FF}}male{{BECBFC}} or a {{95A3FF}}female{{BECBFC}}?", "Male", "Female", Bind(&Dialogs::Sex, this));

	Add(DialogID::kCompleteRegistration, DialogStyle::kMessage, "Registration - Confirmation",
		"Thank you {{95A3FF}}{}{{BECBFC}} for the information. Your character will be for {{95A3FF}}{}{{BECBFC}}.\n\nThis is the last step of the registration, please confirm if you want to finish your registration or to cancel it.",
		"Finish", "Cancel", Bind(&Dialogs::CompleteRegistration, this));

	Add(DialogID::kTutorial, DialogStyle::kMessage, "Tutorial", "Hello {{95A3FF}}{}{{BECBFC}}, do you want to follow our tutorial?\n\nIt will show you few things on this server.", "Yes", "No", 
		Bind(&Dialogs::Tutorial, this));

	Add(DialogID::kAuthentication, DialogStyle::kPassword, "Authentication", "Hello {{95A3FF}}{}{{BECBFC}},\n\nYou have an account on our server, please login to access it.", "Login", "Cancel", 
		Bind(&Dialogs::Authentication, this));
}

void Dialogs::Add(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2, dialogfunction_t Function)
{
	auto NewDialog = std::make_shared<Dialog>(Function);

	NewDialog->SetData<DialogID>(DialogData::kID, ID);
	NewDialog->SetData<DialogStyle>(DialogData::kStyle, Style);
	NewDialog->SetData<std::string>(DialogData::kCaption, Caption);
	NewDialog->SetData<std::string>(DialogData::kText, Text);
	NewDialog->SetData<std::string>(DialogData::kButton1, Button1);
	NewDialog->SetData<std::string>(DialogData::kButton2, Button2);

	m_dialogs.emplace(ID, std::move(NewDialog));
}

Dialog Dialogs::Create(const DialogID& ID, const std::string& Text)
{
	auto Dialog = Get(ID);

	return Create(ID, Dialog->GetStyle(), Dialog->GetCaption(), Text, Dialog->GetButton1(), Dialog->GetButton2(), Dialog->GetFunction());
}

Dialog Dialogs::Create(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1, const std::string& Button2, dialogfunction_t Function)
{
	Dialog Result(Function);

	Result.SetData<DialogID>(DialogData::kID, ID);
	Result.SetData<DialogStyle>(DialogData::kStyle, Style);
	Result.SetData<std::string>(DialogData::kCaption, Caption);
	Result.SetData<std::string>(DialogData::kText, Text);
	Result.SetData<std::string>(DialogData::kButton1, Button1);
	Result.SetData<std::string>(DialogData::kButton2, Button2);

	return Result;
}

bool Dialogs::Execute(std::shared_ptr<Player> Player, const DialogID& ID, const DialogResponse& Response, const size_t ItemIndex, const std::string& Text)
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

const std::shared_ptr<Dialog> Dialogs::Get(const DialogID& ID) const
{
	if (m_dialogs.find(ID) == m_dialogs.end())
	{
		return std::make_shared<Dialog>(dialogfunction_t());
	}

	return m_dialogs.at(ID);
}

void Dialogs::Authentication(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->Kick();
	}
	else
	{
		auto Password = Encryption::Encrypt(Text, Player->GetSalt());

		// TODO: Insert fail authentication log or success log.

		if (Player->GetPassword().compare(Password) == 0)
		{
			Player->SetData<bool>(PlayerData::kAuthenticated, true);
			Player->Spawn();
		}
		else
		{
			Player->ShowDialog(Create(DialogID::kAuthentication, "Sorry {{95A3FF}}{}{{BECBFC}} but password which you entered {{9E0028}}doesn't match{{BECBFC}} with your account's password. Please try again.\n\nPlease type your password below:"), Player->GetName());
		}
	}
}

void Dialogs::CompleteRegistration(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	if (Response == DialogResponse::kRight)
	{
		Player->Kick();
	}
	else
	{
		Player->SetData<bool>(PlayerData::kAuthenticated, true);

		MySQL::GetInstance()->Query(QueryType::kNormal, "INSERT INTO `players` (`Name`, `Password`, `Salt`, `Email`, `Pin`, `Sex`) VALUES (':name', ':password', ':salt', ':email', ':pin', ':sex')",
		{
			MySQL::GetInstance()->MakeParameter("name", Player->GetName()),
			MySQL::GetInstance()->MakeParameter("password", Player->GetData<std::string>(PlayerData::kPassword)),
			MySQL::GetInstance()->MakeParameter("salt", Player->GetSalt()),
			MySQL::GetInstance()->MakeParameter("email", Player->GetEmail()),
			MySQL::GetInstance()->MakeParameter("pin", Player->GetData<std::string>(PlayerData::kPin)),
			MySQL::GetInstance()->MakeParameter("sex", static_cast<unsigned short>(Player->GetSex()))
		}, &Player::OnInserted, Player);

		Player->ShowDialog(DialogID::kTutorial, Player->GetName());
	}
}

void Dialogs::Email(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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

void Dialogs::Pin(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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

void Dialogs::PinConfirmation(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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

void Dialogs::Register(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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

void Dialogs::RegisterConfirmation(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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

void Dialogs::Sex(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
{
	Player->SetData<PlayerSex>(PlayerData::kSex, Response == DialogResponse::kRight ? PlayerSex::kFemale : PlayerSex::kMale);
	Player->ShowDialog(DialogID::kCompleteRegistration, Player->GetName(), Player->GetSex() == PlayerSex::kMale ? "male" : "female");
}

void Dialogs::Tutorial(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text)
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
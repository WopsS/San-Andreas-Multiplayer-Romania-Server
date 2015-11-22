#include <Server/CServer.hpp>

CServer::CServer()
{
}

CServer::~CServer()
{
}

void CServer::Initialize()
{
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `businesses`", {}, this, &CServer::InitializeBusinesses);
	InitializeDialogs();
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `houses`", {}, this, &CServer::InitializeHouses);
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `faction_vehicles`", {}, this, &CServer::InitializeVehicles);
}

void CServer::InitializeBusinesses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CBusiness::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} businesses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeDialogs()
{
	CDialog::Add(DialogID::kRegister, DialogStyle::kPassword, "Registration",
		"Hello {{95A3FF}}{}{{BECBFC}},\n\nYou don't have an account, you need to register in order to play on this server.\nPassword must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 32{{BECBFC}} characters.\n\nPlease type your password below:", 
		"Next", "Cancel");

	CDialog::Add(DialogID::kRegisterConfirmation, DialogStyle::kPassword, "Registration - Password confirmation", 
		"{{95A3FF}}{}{{BECBFC}}, you need to confirm your password to make sure it is the correct one.\n\nPlease type your password below:", "Next", "Back");

	CDialog::Add(DialogID::kEmail, DialogStyle::kInput, "Registration - Email",
		"{{95A3FF}}{}{{BECBFC}}, we need your email because when you forgot your {{95A3FF}}password{{BECBFC}} or your {{95A3FF}}PIN{{BECBFC}} number we will send a new one to you.\n\nPlease type your email below:", 
		"Next", "Back");

	CDialog::Add(DialogID::kPin, DialogStyle::kInput, "Registration - Pin",
		"Thank you {{95A3FF}}{}{{BECBFC}}, your email is {{95A3FF}}{}{{BECBFC}}.\n\nNow you need to enter a {{95A3FF}}PIN number{{BECBFC}} to add a second protection to your account.\nPIN number will be used to {{9E0028}}unlock access{{BECBFC}} for few commands (change password, transfer money, give money to player, etc.).\n\nPin must contains {{9E0028}}minimum 4{{BECBFC}} and {{9E0028}}maximum 8{{BECBFC}} digits.", 
		"Next", "Back");

	CDialog::Add(DialogID::kPinConfirmation, DialogStyle::kMessage, "Registration - Pin confirmation", 
		"We need to be sure about your {{95A3FF}}PIN number{{BECBFC}}.\nCurrent PIN number is {{9E0028}}{}{{BECBFC}}, is that correct?", "Yes", "No");

	CDialog::Add(DialogID::kSex, DialogStyle::kMessage, "Registration - Sex",
		"Thank you {{95A3FF}}{}{{BECBFC}}.\n\nNow please select your sex, are you a {{95A3FF}}male{{BECBFC}} or a {{95A3FF}}female{{BECBFC}}?", "Male", "Female");

	CDialog::Add(DialogID::kCompleteRegistration, DialogStyle::kMessage, "Registration - Confirmation",
		"Thank you {{95A3FF}}{}{{BECBFC}} for the information. Your character will be for {{95A3FF}}{}{{BECBFC}}.\n\nThis is the last step of the registration, please confirm if you want to finish your registration or to cancel it.", 
		"Finish", "Cancel");

	CDialog::Add(DialogID::kTutorial, DialogStyle::kMessage, "Tutorial", "Hello {{95A3FF}}{}{{BECBFC}}, do you want to follow our tutorial?\n\nIt will show you few things on this server.", "Yes", "No");

	CDialog::Add(DialogID::kAuthentication, DialogStyle::kPassword, "Authentication", "Hello {{95A3FF}}{}{{BECBFC}},\n\nYou have an account on our server, please login to access it.", "Login", "Cancel");
}

void CServer::InitializeHouses(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CHouse::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} houses loaded.", Result->GetRowCount()).c_str());
}

void CServer::InitializeVehicles(std::shared_ptr<CResult> Result)
{
	for (uint16_t i = 0; i < Result->GetRowCount(); i++)
	{
		CVehicle::Add(i, Result);
	}

	sampgdk::logprintf(fmt::format("CServer::Initialize: {} vehicles loaded.", Result->GetRowCount()).c_str());
}

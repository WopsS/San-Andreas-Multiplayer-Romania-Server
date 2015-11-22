#include <Player/CPlayer.hpp>

#include <random>
#include <regex>
#include <sstream>

#include <MySQL/CMySQL.hpp>
#include <Utilities/Encryption.hpp>
#include <Utilities/Utils.hpp>

CPlayer::CPlayer(uint16_t aID)
{
	char Name[MAX_PLAYER_NAME + 1];
	sampgdk::GetPlayerName(aID, Name, sizeof(Name));

	std::stringstream StringStream;
	StringStream << Name;

	AddData<uint16_t>(PlayerData::kGameID, aID);
	AddData<std::string>(PlayerData::kName, StringStream.str());
	AddData<bool>(PlayerData::kAuthenticated, false);
}

CPlayer::~CPlayer()
{
}

void CPlayer::OnConnect(std::shared_ptr<CResult> Result)
{
	if (Result->GetRowCount() > 0) // Player has an account in database, store the information.
	{
		// Load user information from database.

		auto Length = static_cast<size_t>(PlayerData::kEndMySQL);

		for (size_t i = 0; i < Length; i++)
		{
			auto Index = static_cast<PlayerData>(i);

			// Let's do few custom cases.
			if (i == static_cast<size_t>(PlayerData::kMySQLID))
			{
				SetData<uint64_t>(PlayerData::kMySQLID, std::stoull(Result->GetRowData(Index)));
			}
			else if (i == static_cast<size_t>(PlayerData::kSex))
			{
				SetData<PlayerSex>(PlayerData::kSex, static_cast<PlayerSex>(std::stoi(Result->GetRowData(Index))));
			}
			else
			{
				auto Value = Result->GetRowData(Index);

				if (Utils::IsNumber(Value) == true)
				{
					SetData<uint32_t>(Index, std::stoul(Result->GetRowData(Index)));
				}
				else
				{
					SetData<std::string>(Index, Result->GetRowData(Index));
				}
			}
		}

		// Show the dialog if user isn't authenticated.
		if (IsAuthenticated() == false)
		{
			ShowDialog(DialogID::kAuthentication, GetName());
		}
	}
	else // Player doesn't have an account in database.
	{
		ShowDialog(DialogID::kRegister, GetName());
	}
}

void CPlayer::OnDisconnect(const DisconnectReason& Reason)
{
	// TODO: Save player data.
}

bool CPlayer::OnDialogResponse(const DialogID& ID, const DialogResponse& Response, const uint32_t Item, const std::string& Text)
{
	auto Found = true;

	switch (ID)
	{
		case DialogID::kRegister:
		{
			// If player press 'Cancel' button let's kick him.
			if (Response == DialogResponse::kRight)
			{
				Kick();
			}
			else
			{
				if (Text.length() < 4 || Text.length() > 32)
				{
					ShowDialog(DialogID::kRegister, GetName());
				}
				else
				{
					// Generate salt for the user and encrypt the password.
					std::random_device RandomDevice;
					std::default_random_engine RandomEngine(RandomDevice());
					std::uniform_int_distribution<int> uniform_dist(12, 32);

					SetData<std::string>(PlayerData::kSalt, Encryption::GenerateSalt(64 + uniform_dist(RandomEngine)));
					SetData<std::string>(PlayerData::kPassword, Encryption::Encrypt(Text, GetSalt()));

					ShowDialog(DialogID::kRegisterConfirmation, GetName());
				}
			}

			break;
		}
		case DialogID::kRegisterConfirmation:
		{
			if (Response == DialogResponse::kRight)
			{
				ShowDialog(DialogID::kRegister, GetName());
			}
			else
			{
				auto Password = Encryption::Encrypt(Text, GetSalt());

				if (GetData<std::string>(PlayerData::kPassword).compare(Password) == 0)
				{
					ShowDialog(DialogID::kEmail, GetName());
				}
				else
				{
					auto CurrentDialog = CDialog::Get(DialogID::kRegisterConfirmation);

					CDialog Dialog(DialogID::kRegisterConfirmation, CurrentDialog->GetStyle(), CurrentDialog->GetCaption(),
						"Sorry {{95A3FF}}{}{{BECBFC}} but your confirmation password {{9E0028}}doesn't match{{BECBFC}} with your password. Please try again.\n\nPlease type your password below:",
						CurrentDialog->GetButton1(), CurrentDialog->GetButton2());

					ShowDialog(Dialog, GetName());
				}
			}

			break;
		}
		case DialogID::kEmail:
		{
			if (Response == DialogResponse::kRight)
			{
				ShowDialog(DialogID::kRegister, GetName());
			}
			else
			{
				std::regex Regex("^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");

				// Check if the email is valid.
				if (std::regex_search(Text, Regex))
				{
					SetData<std::string>(PlayerData::kEmail, Text);
					ShowDialog(DialogID::kPin, GetName(), GetEmail());
				}
				else
				{
					ShowDialog(DialogID::kEmail, GetName());
				}
			}

			break;
		}
		case DialogID::kPin:
		{
			if (Response == DialogResponse::kRight)
			{
				ShowDialog(DialogID::kEmail, GetName());
			}
			else
			{
				if (Text.length() < 4 || Text.length() > 8 || Utils::IsNumber(Text) == false)
				{
					ShowDialog(DialogID::kPin, GetName(), GetEmail());
				}
				else
				{
					SetData<std::string>(PlayerData::kPin, Encryption::Encrypt(Text, GetSalt()));
					ShowDialog(DialogID::kPinConfirmation, Text);
				}
			}

			break;
		}
		case DialogID::kPinConfirmation:
		{
			if (Response == DialogResponse::kRight)
			{
				ShowDialog(DialogID::kPin, GetName(), GetEmail());
			}
			else
			{
				ShowDialog(DialogID::kSex, GetName());
			}

			break;
		}
		case DialogID::kSex:
		{
			SetData<PlayerSex>(PlayerData::kSex, Response == DialogResponse::kRight ? PlayerSex::kFemale : PlayerSex::kMale);
			ShowDialog(DialogID::kCompleteRegistration, GetName(), GetSex() == PlayerSex::kMale ? "male" : "female");

			break;
		}
		case DialogID::kCompleteRegistration:
		{
			if (Response == DialogResponse::kRight)
			{
				Kick();
			}
			else
			{
				SetData<bool>(PlayerData::kAuthenticated, true);

				CMySQL::GetInstance()->Query(QueryType::kNormal, "INSERT INTO `players` (`Name`, `Password`, `Salt`, `Email`, `Pin`, `Sex`) VALUES (':name', ':password', ':salt', ':email', ':pin', ':sex')",
				{ 
					CMySQL::GetInstance()->MakeParameter("name", GetName()),
					CMySQL::GetInstance()->MakeParameter("password", GetData<std::string>(PlayerData::kPassword)),
					CMySQL::GetInstance()->MakeParameter("salt", GetSalt()),
					CMySQL::GetInstance()->MakeParameter("email", GetEmail()),
					CMySQL::GetInstance()->MakeParameter("pin", GetData<std::string>(PlayerData::kPin)),
					CMySQL::GetInstance()->MakeParameter("sex", static_cast<uint16_t>(GetSex()))
				}, this, &CPlayer::OnInserted);

				ShowDialog(DialogID::kTutorial, GetName());
			}

			break;
		}
		case DialogID::kTutorial:
		{
			// TODO: Spawn player if he press 'No' or put him in tutorial if he press 'Yes'.

			if (Response == DialogResponse::kRight)
			{
				Spawn();
			}
			else
			{
				Spawn();
			}

			break;
		}
		case DialogID::kAuthentication:
		{
			if (Response == DialogResponse::kRight)
			{
				Kick();
			}
			else
			{
				auto Password = Encryption::Encrypt(Text, GetSalt());

				// TODO: Insert fail authentication log or success log.

				if (GetData<std::string>(PlayerData::kPassword).compare(Password) == 0)
				{
					SetData<bool>(PlayerData::kAuthenticated, true);
					Spawn();
				}
				else
				{
					auto CurrentDialog = CDialog::Get(DialogID::kAuthentication);

					CDialog Dialog(DialogID::kAuthentication, CurrentDialog->GetStyle(), CurrentDialog->GetCaption(),
						"Sorry {{95A3FF}}{}{{BECBFC}} but password which you entered {{9E0028}}doesn't match{{BECBFC}} with your account's password. Please try again.\n\nPlease type your password below:",
						CurrentDialog->GetButton1(), CurrentDialog->GetButton2());

					ShowDialog(Dialog, GetName());
				}
			}

			break;
		}
		default:
		{
			Found = false;
			break;
		}
	}

	return Found;
}

void CPlayer::OnInserted(std::shared_ptr<CResult> Result)
{
	SetData<uint64_t>(PlayerData::kMySQLID, static_cast<uint64_t>(Result->GetInsertedID()));
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `ID` = ':id' LIMIT 1", { CMySQL::GetInstance()->MakeParameter("id", GetMySQLID()) }, this, &CPlayer::OnConnect);
}

void CPlayer::OnSpawn()
{
}

const std::string CPlayer::GetEmail() const
{
	return GetData<std::string>(PlayerData::kEmail);
}

uint16_t CPlayer::GetGameID() const
{
	return GetData<uint16_t>(PlayerData::kGameID);
}

uint64_t CPlayer::GetMySQLID() const
{
	return GetData<uint64_t>(PlayerData::kMySQLID);
}

const std::string CPlayer::GetName() const
{
	return GetData<std::string>(PlayerData::kName);
}

const std::string CPlayer::GetSalt() const
{
	return GetData<std::string>(PlayerData::kSalt);
}

const PlayerSex CPlayer::GetSex() const
{
	return GetData<PlayerSex>(PlayerData::kSex);
}

bool CPlayer::IsAuthenticated() const
{
	return GetData<bool>(PlayerData::kAuthenticated);
}

bool CPlayer::Kick() const
{
	return sampgdk::Kick(GetGameID());
}

bool CPlayer::SetPosition(const float X, const float Y, const float Z, const float Angle, const uint32_t Interior, const uint32_t VirtualWorld) const
{
	return sampgdk::SetPlayerPos(GetGameID(), X, Y, Z);
}

bool CPlayer::Spawn()
{
	if (GetData<bool>(PlayerData::kSpectating) == true)
	{
		return ToggleSpectating(false);
	}

	return sampgdk::SpawnPlayer(GetGameID());
}

bool CPlayer::ToggleSpectating(const bool Toggle)
{
	SetData<bool>(PlayerData::kSpectating, Toggle);
	return sampgdk::TogglePlayerSpectating(GetGameID(), Toggle);
}

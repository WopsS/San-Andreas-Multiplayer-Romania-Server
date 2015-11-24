#include <Player/CPlayer.hpp>

#include <sstream>

#include <Dialog/CDialogs.hpp>
#include <MySQL/CMySQL.hpp>
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
			auto Value = Result->GetRowData(Index);

			// Let's do few custom cases.
			if (i == static_cast<size_t>(PlayerData::kMySQLID))
			{
				SetData<uint64_t>(PlayerData::kMySQLID, std::stoull(Value));
			}
			else if (i == static_cast<size_t>(PlayerData::kSex))
			{
				SetData<PlayerSex>(PlayerData::kSex, static_cast<PlayerSex>(std::stoi(Value)));
			}
			else
			{
				auto IsFloat = Utils::IsFloat(Value);
				auto IsInteger = Utils::IsInteger(Value);
				auto IsString = IsFloat == false && IsInteger == false;

				if (IsString == true)
				{
					SetData<std::string>(Index, Value);
				}
				else if (IsInteger == true) // Check if it is a number after we check if it is as string because if the number is '0' it will return true at 'IsFloat', so probably if it is 0 it is an integer.
				{
					SetData<uint32_t>(Index, std::stoul(Value));
				}
				else if (IsFloat == true)
				{
					SetData<float>(Index, std::stof(Value));
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

void CPlayer::OnInserted(std::shared_ptr<CResult> Result)
{
	SetData<uint64_t>(PlayerData::kMySQLID, static_cast<uint64_t>(Result->GetInsertedID()));
	CMySQL::GetInstance()->Query(QueryType::kNormal, "SELECT * FROM `players` WHERE `ID` = ':id' LIMIT 1", { CMySQL::GetInstance()->MakeParameter("id", GetMySQLID()) }, &CPlayer::OnConnect, this);
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

std::shared_ptr<CDialog> CPlayer::GetDialog(const DialogID& ID)  const
{
	return CDialogs::GetInstance()->Get(ID);
}

#include <stdafx.hpp>
#include <Dialogs/Player/Authentication.hpp>
#include <Player/Player.hpp>

AuthenticationDialog::AuthenticationDialog()
{
	m_id = DialogID::kAuthentication;
	m_style = DialogStyle::kPassword;
	m_caption = "Authentication";
	m_text = "Hello {{95A3FF}}{}{{BECBFC}},\n\nYou have an account on our server, please login to access it.";
	m_buttons[0] = "Login";
	m_buttons[1] = "Cancel";
}

const bool AuthenticationDialog::CustomAccess(std::shared_ptr<Player> Player) const
{
	return true;
}

void AuthenticationDialog::Execute(std::shared_ptr<Player> Player, const DialogResponse & Response, const size_t ItemIndex, const std::string & Text)
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
			Player->SetAuthenticationState(true);
			Player->Spawn();
		}
		else
		{
			AuthenticationDialog Authentication;

			Authentication.m_id = m_id;
			Authentication.m_style = m_style;
			Authentication.m_caption = m_caption;
			Authentication.m_text = "Sorry {{95A3FF}}{}{{BECBFC}} but password which you entered {{9E0028}}doesn't match{{BECBFC}} with your account's password. Please try again.\n\nPlease type your password below:";
			Authentication.m_buttons[0] = m_buttons[0];
			Authentication.m_buttons[1] = m_buttons[1];

			Player->ShowDialog(Authentication, Player->GetName());
		}
	}
}

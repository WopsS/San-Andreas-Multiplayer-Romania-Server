#pragma once

#include <Dialogs/Enums.hpp>
#include <Dialogs/CustomDialog.hpp>

class Player;

class Dialogs : public Singleton<Dialogs>
{
public:

	CustomDialog Create(const DialogID& ID, const std::string& Text);

	CustomDialog Create(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string Buttons[2]);

	bool Execute(std::shared_ptr<Player> Player, const DialogID& ID, const DialogResponse& Response, const size_t ItemIndex, const std::string& Tex);

	const std::shared_ptr<Dialog> Get(const DialogID& ID) const;

private:

	friend class Singleton<Dialogs>;

	Dialogs();
	~Dialogs() = default;

	void Register(std::shared_ptr<Dialog> Dialog);

	/*void Add(const DialogID& ID, const DialogStyle& Style, const std::string& Caption, const std::string& Text, const std::string& Button1 = "Close", const std::string& Button2 = "", dialogfunction_t Function = nullptr);
	
	template<typename F, typename C>
	inline dialogfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	}

	void Authentication(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void CompleteRegistration(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void Email(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void Pin(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void PinConfirmation(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void Register(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void RegisterConfirmation(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void Sex(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);

	void Tutorial(std::shared_ptr<Player> Player, DialogResponse Response, size_t ItemIndex, std::string Text);*/

	std::unordered_map<DialogID, std::shared_ptr<Dialog>, HashType<DialogID>> m_dialogs;
};
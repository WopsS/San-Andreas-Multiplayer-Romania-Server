#pragma once

#include <Player/Player.hpp>
#include <House/House.hpp>

#define KEY_NONE 0

class Keys : public Singleton<Keys>
{
public:

	void OnPresses(std::shared_ptr<Player> Player, int NewKeys, int OldKeys);

private:

	friend class Singleton<Keys>;

	Keys();
	~Keys() = default;

	void Register(int Keys, bool Holding, keyfunction_t Function, int OldKeys = KEY_NONE);

	template<typename F, typename C>
	inline keyfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1);
	}

	void Enter(std::shared_ptr<Player> Player);

	void Exit(std::shared_ptr<Player> Player);
	
	std::map<int, std::tuple<bool, keyfunction_t, int>> m_keys;
};
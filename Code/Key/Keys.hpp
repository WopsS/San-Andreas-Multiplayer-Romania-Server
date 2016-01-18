#pragma once

#include <Player/Player.hpp>
#include <House/House.hpp>

#define KEY_NONE 0

class Keys : public Singleton<Keys>
{
public:

	void OnPress(std::shared_ptr<Player> Player, int32_t NewKeys, int32_t OldKeys);

private:

	friend class Singleton<Keys>;

	typedef std::function<void(std::shared_ptr<Player>)> keyfunction_t;

	Keys();
	~Keys() = default;

	void Register(int32_t Keys, bool Holding, keyfunction_t Function, int32_t OldKeys = KEY_NONE);

	template<typename F, typename C>
	inline keyfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1);
	}

	void Enter(std::shared_ptr<Player> Player);

	void Exit(std::shared_ptr<Player> Player);
	
	std::map<int32_t, std::tuple<bool, keyfunction_t, int32_t>> m_keys;
};
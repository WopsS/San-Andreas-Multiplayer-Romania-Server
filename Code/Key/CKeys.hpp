#pragma once

#include <map>
#include <memory>
#include <tuple>

#include <Base/CSingleton.hpp>
#include <Player/CPlayer.hpp>

#define KEY_NONE 0

class CKeys : public CSingleton<CKeys>
{
public:

	void OnPresses(std::shared_ptr<CPlayer> Player, int NewKeys, int OldKeys);

private:

	friend class CSingleton<CKeys>;

	CKeys();
	~CKeys() = default;

	void Register(int Keys, bool Holding, keyfunction_t Function, int OldKeys = KEY_NONE);

	template<typename F, typename C>
	inline keyfunction_t Bind(F Function, C Class)
	{
		return std::bind(Function, Class, std::placeholders::_1);
	}

	void Test1(std::shared_ptr<CPlayer> Player);

	void Test2(std::shared_ptr<CPlayer> Player);

	void Test3(std::shared_ptr<CPlayer> Player);

	std::map<int, std::tuple<bool, keyfunction_t, int>> m_keys;
};
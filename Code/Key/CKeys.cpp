#include <Key/CKeys.hpp>
#include <Base/Cpoint.hpp>
#include <Base/CData.hpp>
#include <House/CHouse.hpp>
#include <Business/CBusiness.hpp>

CKeys::CKeys()
{
	Register(KEY_FIRE, false, Bind(&CKeys::Test1, this));
	Register(KEY_SECONDARY_ATTACK | KEY_JUMP, true, Bind(&CKeys::Test2, this));
	Register(KEY_SPRINT, true, Bind(&CKeys::Test3, this), KEY_WALK);
}

void CKeys::Register(int Keys, bool Holding, keyfunction_t Function, int OldKeys)
{
	m_keys.emplace(Keys, std::make_tuple(Holding, Function, OldKeys));
}

void CKeys::OnPresses(std::shared_ptr<CPlayer> Player, int NewKeys, int OldKeys)
{
	bool NeedHolding = false;
	int lOldKeys;

	for (auto& i : m_keys)
	{
		NeedHolding = std::get<0>(i.second);
		lOldKeys = std::get<2>(i.second);

		// Check if the key must be holded.
		if ((NeedHolding == false && (NewKeys & i.first)) || (NeedHolding == true && (NewKeys & i.first) == i.first))
		{
			// Check if we have some old keys and they are equal with function keys.
			if (lOldKeys != KEY_NONE && (!(OldKeys & lOldKeys) || (OldKeys & lOldKeys) != lOldKeys))
			{
				break;
			}

			auto KeyFunction = std::bind(std::get<1>(i.second), Player);

			// Call the key's function.
			KeyFunction();

			break;
		}
	}
}

void CKeys::Test1(std::shared_ptr<CPlayer> Player)
{
	Player->SendMessage(Colors::kWhite, "Test1 - Pressed");
}

void CKeys::Test2(std::shared_ptr<CPlayer> Player)
{
	Player->SendMessage(Colors::kWhite, "Test2 - Holding");
}

void CKeys::Test3(std::shared_ptr<CPlayer> Player)
{
	Player->SendMessage(Colors::kWhite, "Test3 - Old key");
}

void CKeys::Enter(std::shared_ptr<CPlayer> Player)
{
	std::shared_ptr<CHouse> House = nullptr;

	for (auto& i : CHouse::GetList())
	{
		auto Position = House->GetData<Point3D<float>>(HouseData::kEntrance);
		auto Lock = House->GetData<uint16_t>(HouseData::kLock);

		House = i.second;

		if (Lock == 1)
		{
			Player->SendMessage(0xFFFFFF, "This door is lock!");
		}
		if (Player->IsInRangeOfPoint(Position, 2.0f))
		{
			Player->SetPosition(Position);
		}
	}

	std::shared_ptr<CBusiness> Bizz = nullptr;

	for (auto& i : CBusiness::GetList())
	{
		auto Position = Bizz->GetData<Point3D<float>>(BusinessData::kEnterance);
		auto Lock = Bizz->GetData<uint16_t>(BusinessData::kLock);

		Bizz = i.second;

		if (Lock == 1)
		{
			Player->SendMessage(0xFFFFFF, "This door is lock!");
		}
		if (Player->IsInRangeOfPoint(Position, 2.0f))
		{
			Player->SetPosition(Position);
		}
	}
}

void CKeys::Exit(std::shared_ptr<CPlayer> Player)
{
	std::shared_ptr<CHouse> House = nullptr;

	for (auto& i : CHouse::GetList())
	{
		House = i.second;

		auto Position = House->GetData<Point3D<float>>(HouseData::kExit);

		if (Player->IsInRangeOfPoint(Position))
		{
			if (House->GetData<uint16_t>(HouseData::kLock) == 1)
			{
				Player->SendMessage(0xFFFFFF, "This door is lock!");
			}
			else
			{
				Player->SetPosition(Position);
			}

			return;
		}
	}
	std::shared_ptr<CBusiness> Business = nullptr;

	for (auto& i : CBusiness::GetList())
	{
		Business = i.second;

		auto Position = Business->GetData<Point3D<float>>(BusinessData::kExit);
		auto Lock = Business->GetData<uint16_t>(BusinessData::kLock);

		if (Lock == 1)
		{
			Player->SendMessage(0xFFFFFF, "This door is lock!");
		}
		if (Player->IsInRangeOfPoint(Position, 2.0f))
		{
			Player->SetPosition(Position);
		}
	}
}

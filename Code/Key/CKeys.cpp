#include <Key/CKeys.hpp>

#include <House/CHouse.hpp>
#include <Business/CBusiness.hpp>

CKeys::CKeys()
{
	Register(KEY_FIRE, false, Bind(&CKeys::Enter, this));
	Register(KEY_FIRE, false, Bind(&CKeys::Exit, this));
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
		}
	}
}

void CKeys::Enter(std::shared_ptr<CPlayer> Player)
{
	for (auto& i : CHouse::GetList())
	{
		auto House = i.second;

		if (Player->IsInRangeOfPoint(House->GetData<Point3D<float>>(HouseData::kEntrance)))
		{
			if (!!House->GetData<uint16_t>(HouseData::kLocked) == true)
			{
				Player->SendMessage(0xFFFFFF, "* The house's door is locked, you cannot enter.");
			}
			else
			{
				Player->SetPosition(House->GetData<Point3D<float>>(HouseData::kExit));
			}

			return;
		}
	}

	for (auto& i : CBusiness::GetList())
	{
		auto Business = i.second;

		if (Player->IsInRangeOfPoint(Business->GetData<Point3D<float>>(BusinessData::kEntrance)))
		{
			if (!!Business->GetData<uint16_t>(BusinessData::kLocked) == true)
			{
				Player->SendMessage(0xFFFFFF, "The business's door is locked, you cannot enter.");
			}
			else
			{
				Player->SetPosition(Business->GetData<Point3D<float>>(BusinessData::kExit));
			}

			return;
		}
	}
}

void CKeys::Exit(std::shared_ptr<CPlayer> Player)
{
	for (auto& i : CHouse::GetList())
	{
		auto House = i.second;

		if (Player->IsInRangeOfPoint(House->GetData<Point3D<float>>(HouseData::kExit)))
		{
			Player->SetPosition(House->GetData<Point3D<float>>(HouseData::kEntrance));
			return;
		}
	}

	for (auto& i : CBusiness::GetList())
	{
		auto Business = i.second;

		if (Player->IsInRangeOfPoint(Business->GetData<Point3D<float>>(BusinessData::kExit)))
		{
			Player->SetPosition(Business->GetData<Point3D<float>>(BusinessData::kEntrance));
			return;
		}
	}
}

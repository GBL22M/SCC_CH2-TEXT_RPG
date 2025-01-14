#include "Shop.h"

void Shop::SetItems(Item* NewItem)
{
	if (AvailableItems.size() == FIX_ITEM + WPN_ITEM)
	{
		for (int i = 0; i < WPN_ITEM; i++)
			AvailableItems.pop_back();
	}
	AvailableItems.push_back(NewItem);
}

void Shop::DisplayItems()
{
	cout << "\n==============SHOP==================\n\n";

	for (int i = 0; i < AvailableItems.size(); i += 2)
	{
		cout << i + 1 << ". " << AvailableItems[i]->GetName() << "\t";
		if (i < AvailableItems.size() - 1) cout << i + 2 << ". " << AvailableItems[i + 1]->GetName() << endl;
		else cout << endl;
		cout << "   " << AvailableItems[i]->GetBuyPrice() << "gold" << "\t";
		if (i < AvailableItems.size() - 1) cout << "   " << AvailableItems[i + 1]->GetBuyPrice() << "gold" << endl;
		else cout << endl;
	}

	cout << "\n====================================\n\n";
}

void Shop::BuyItem(int idx, Character* player)
{
	int PlayerGold = player->GetGold();

	Item* BuyItem = AvailableItems[idx];
	Item* NewItem;
	int ItemPrice = BuyItem->GetBuyPrice();

	if (PlayerGold >= ItemPrice)
	{
		player->SetInventory(BuyItem);
		player->SetGold(-ItemPrice);
		if (idx < FIX_ITEM)
		{
			switch (idx)
			{
			case 0:
				NewItem = new HealthPotion();
				break;
			case 1:
				NewItem = new AttackBoost();
				break;
			default:
				NewItem = nullptr;
				break;
			}
			AvailableItems[idx] = NewItem;
		}
		else AvailableItems.erase(AvailableItems.begin() + idx);
	}
	else
		cout << "골드가 부족하여 구매에 실패했습니다." << endl;
}

void Shop::SellItem(int idx, Character* player)
{
	if (idx < 0 || idx >= player->GetInventory().size()) {
		cout << "잘못된 아이템 번호입니다.\n";
		return;
	}
	Item* item = player->GetInventory()[idx];
	Weapon* weapon = dynamic_cast<Weapon*>(item);

	if (weapon && weapon == Weapon::GetEquippedWeapon()) {
		weapon->Use(player);
	}
	Item* temp = player->GetInventory()[idx];

	player->SellItem(idx);
	temp->SellItem(player);
	cout << "아이템을 판매했습니다.\n";
}

void Shop::GetInfo(int idx)
{
	AvailableItems[idx]->printInfo();
}

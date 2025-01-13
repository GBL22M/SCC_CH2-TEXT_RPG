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
		cout << i + 2 << ". " << AvailableItems[i + 1]->GetName() << endl;
		cout << "   " << AvailableItems[i]->GetBuyPrice() << "gold" << "\t";
		cout << "   " << AvailableItems[i + 1]->GetBuyPrice() << "gold" << endl;
	}

	cout << "\n====================================\n\n";
}

void Shop::BuyItem(int idx, Character* player)
{
	int PlayerGold = player->GetGold();
	int ItemPrice = AvailableItems[idx]->GetBuyPrice();
	
	if (PlayerGold >= ItemPrice)
	{
		player->SetInventory(AvailableItems[idx]);
		player->SetGold(PlayerGold - ItemPrice);
	}
	else
		cout << "골드가 부족하여 구매에 실패했습니다." << endl;
}

void Shop::SellItem(int idx, Character* player)
{
	Item* temp = player->GetInventory()[idx];

	player->SellItem(idx);

	temp->SellItem(player);
}

void Shop::GetInfo(int idx)
{
	AvailableItems[idx]->printInfo();
}

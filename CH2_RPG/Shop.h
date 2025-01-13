#pragma once

#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Character.h"
#include <iostream>

#define FIX_ITEM 2
#define WPN_ITEM 2

using namespace std;

class Shop
{
public:
	Shop()
	{
		Item* Potion = new HealthPotion();			//Default shop item
		Item* AtkBoost = new AttackBoost();

		AvailableItems.push_back(Potion);
		AvailableItems.push_back(AtkBoost);
	}
	void SetItems(Item* NewItem);

	void DisplayItems();

	void BuyItem(int idx, Character* player);
	void SellItem(int idx, Character* player);

	void GetInfo(int idx);

private:
	vector<Item*> AvailableItems;
};


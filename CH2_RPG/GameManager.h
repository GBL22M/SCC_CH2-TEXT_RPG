#pragma once
#include "Character.h"
#include "Monster.h"
#include "Weapon.h"

#define WPN_DEF 2

class GameManager
{
public:
	Monster* GenerateMonster(int level);
	bool Battle(Character* player);
	void DisplayInventory(Character* player);

	Item* GenerateWeapon(Character* Player);
	void UseShop(Character* Player);

private:
	const int mTotalMonsterCount = 3;
};
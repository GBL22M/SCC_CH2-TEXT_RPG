#pragma once
#include "Character.h"
#include "Monster.h"
#include "Weapon.h"
#include "RandomIntGenerator.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

#define WPN_DEF 2


class GameManager
{
public:
	Monster* GenerateMonster(int level);
	bool Battle(Character* player);
	void DisplayInventory(Character* player);
	void ManageInventory(Character* player);

	Item* GenerateWeapon(Character* Player);
	void UseShop(Character* Player);

	bool MonsterDeadCheck(Character* player, Monster* monster);
	bool PlayerDeadCheck(Character* player);
	bool GetGameOverFlag() { return GameOverFlag; }
private:
	const int mTotalMonsterCount = 3;
	bool GameOverFlag = false;
};
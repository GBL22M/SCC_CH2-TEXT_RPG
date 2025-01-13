#pragma once
#include "Character.h"
#include "Monster.h"
#include "RandomIntGenerator.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

class GameManager
{
public:
	Monster* GenerateMonster(int level);
	bool Battle(Character* player);
	void DisplayInventory(Character* player);

private:
	const int mTotalMonsterCount = 3;
};

bool MonsterDeadCheck(Character* player, Monster* monster);

bool PlayerDeadCheck(Character* player);
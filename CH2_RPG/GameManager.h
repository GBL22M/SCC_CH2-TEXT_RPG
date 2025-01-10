#pragma once
#include "Character.h"
#include "Monster.h"

class GameManager
{
public:
	Monster* GenerateMonster(int level);
	bool Battle(Character* player);
	void DisplayInventory(Character* player);
	
private:
	const int mTotalMonsterCount = 3;
};
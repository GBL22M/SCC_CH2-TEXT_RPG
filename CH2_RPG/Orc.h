#pragma once

#include "Monster.h"

class Orc :public Monster
{
public:
	Orc(int level);
	string GetName() override;
	int GetHealth() override;
	int GetAttack() override;
	void TakeDamage(int damage) override;

private:
	string mName;
	int mHealth;
	int mAttack;
};
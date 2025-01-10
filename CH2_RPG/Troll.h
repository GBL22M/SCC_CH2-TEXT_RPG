#pragma once

#include "Monster.h"

class Troll : public Monster
{
public:
	Troll(int level);
	string GetName() override;
	int GetHealth() override;
	int GetAttack() override;
	void TakeDamage(int damage) override;

private:
	string mName;
	int mHealth;
	int mAttack;
};
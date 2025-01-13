#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
	BossMonster(int level);
	string GetName() override;
	int GetHealth() override;
	int GetAttack() override;
	void TakeDamage(int damage) override;
	int SkillAttackDamage();

private:
	string mName;
	int mHealth;
	int mAttack;
};
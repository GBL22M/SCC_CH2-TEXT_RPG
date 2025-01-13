#include <iostream>

#include "BossMonster.h"
#include "RandomIntGenerator.h"

BossMonster::BossMonster(int level)
	:mName("Boss Monster")
	,mHealth(2000)
	,mAttack(250)
{
}

string BossMonster::GetName()
{
	return mName;
}

int BossMonster::GetHealth()
{
	if (mHealth <= 0)
		mHealth = 0;
	return mHealth;
}

int BossMonster::GetAttack()
{
	return mAttack;
}

void BossMonster::TakeDamage(int damage)
{
	mHealth -= damage;
}

int BossMonster::SkillAttackDamage()
{
	return GetRandomInt(50, 150);
}

#include "RandomIntGenerator.h"
#include "Orc.h"

Orc::Orc(int level)
	:mName("Orc")
	,mHealth(0)
	,mAttack(0)
{
	mHealth = GetRandomInt(level * 20, level * 30);
	mAttack = GetRandomInt(level * 5, level * 10);
}

string Orc::GetName()
{
	return mName;
}

int Orc::GetHealth()
{
	if (mHealth <= 0)
		mHealth = 0;
	return mHealth;
}

int Orc::GetAttack()
{
	return mAttack;
}

void Orc::TakeDamage(int damage)
{
	mHealth -= damage;
}

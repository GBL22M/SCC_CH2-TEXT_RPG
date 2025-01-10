#include <random>

#include "RandomIntGenerator.h"
#include "Goblin.h"

Goblin::Goblin(int level)
    :mName("Goblin")
    ,mHealth(0)
    ,mAttack()
{
    mHealth = GetRandomInt(level * 20, level * 30);
    mAttack = GetRandomInt(level * 5, level * 10);
}

string Goblin::GetName()
{
    return mName;
}

int Goblin::GetHealth()
{
    if (mHealth <= 0)
        mHealth = 0;
    return mHealth;
}

int Goblin::GetAttack()
{
    return mAttack;
}

void Goblin::TakeDamage(int damage)
{
    mHealth -= damage;
}

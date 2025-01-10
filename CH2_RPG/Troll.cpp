#include "RandomIntGenerator.h"
#include "Troll.h"

Troll::Troll(int level)
    :mName("Troll")
    ,mHealth(0)
    ,mAttack(0)
{
    mHealth = GetRandomInt(level * 20, level * 30);
    mAttack = GetRandomInt(level * 5, level * 10);
}

string Troll::GetName()
{
    return mName;
}

int Troll::GetHealth()
{
    if (mHealth <= 0)
        mHealth = 0;
    return mHealth;
}

int Troll::GetAttack()
{
    return mAttack;
}

void Troll::TakeDamage(int damage)
{
    mHealth -= damage;
}

#include "RandomIntGenerator.h"
#include "Slime.h"

Slime::Slime(int level)
    :mName("Slime")
    , mHealth(0)
    , mAttack()
{
    mHealth = GetRandomInt(level * 20, level * 30);
    mAttack = GetRandomInt(level * 5, level * 10);
}

string Slime::GetName()
{
    return mName;
}

int Slime::GetHealth()
{
    if (mHealth <= 0)
        mHealth = 0;
    return mHealth;
}

int Slime::GetAttack()
{
    return mAttack;
}

void Slime::TakeDamage(int damage)
{
    mHealth -= damage;
}

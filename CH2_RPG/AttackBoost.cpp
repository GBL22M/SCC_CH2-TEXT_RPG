#include "AttackBoost.h"
#include "Character.h"

AttackBoost::AttackBoost()
	:mName("Attack Boost")
	,mAttackIncrease(10)
{
}

string AttackBoost::GetName()
{
	return mName;
}

void AttackBoost::Use(Character* character)
{
	character->SetAttack(mAttackIncrease);
	character->UseItem(1);
}

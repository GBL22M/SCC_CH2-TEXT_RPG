#include "AttackBoost.h"
#include "Character.h"

AttackBoost::AttackBoost()
	:mName("Attack Boost")
	,mAttackIncrease(10)
	,nBuyPrice(20)
{
	nSellPrice = (int)(nBuyPrice * 0.7);
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

void AttackBoost::SellItem(Character* character)
{
	character->SetGold(nSellPrice); delete this;
}

void AttackBoost::printInfo()
{
	cout << mName << " | 추가 공격력 : " << mAttackIncrease << " | 판매가 : " << nSellPrice << endl;
}

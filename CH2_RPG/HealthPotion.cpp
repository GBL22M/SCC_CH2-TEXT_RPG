#include "HealthPotion.h"
#include "Character.h"

HealthPotion::HealthPotion()
	:mName("HealthPotion")
	,mHealthRestore(50)
	,nBuyPrice(10)
{
	nSellPrice = (int)(nBuyPrice * 0.7);
}

string HealthPotion::GetName()
{
	return mName;
}

void HealthPotion::Use(Character* character)
{
	character->SetHealth(mHealthRestore);
	character->UseItem(0);	
}

void HealthPotion::SellItem(Character* character)
{
	character->SetGold(nSellPrice); delete this;
}

void HealthPotion::printInfo()
{
	cout << mName << " | 회복량 : " << mHealthRestore << endl;
}

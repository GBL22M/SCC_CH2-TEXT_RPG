#include "HealthPotion.h"
#include "Character.h"

HealthPotion::HealthPotion()
	:mName("HealthPotion")
	,mHealthRestore(50)
{
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

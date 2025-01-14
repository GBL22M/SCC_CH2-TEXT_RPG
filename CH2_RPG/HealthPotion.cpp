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

bool HealthPotion::Use(Character* character)
{
	int currentHealth = character->GetHealth();
	int maxHealth = character->GetMaxHealth();
	int remainingHealth = maxHealth - currentHealth;

	if (remainingHealth <= 0) {
		cout << "체력이 이미 최대치입니다. 포션을 사용할 수 없습니다.\n";
		return false;
	}

	if (mHealthRestore > remainingHealth) {
		cout << "체력이 " << remainingHealth << "만큼만 회복 가능합니다. 포션의 전체 회복량("
			<< mHealthRestore << ")을 모두 사용할 수 없습니다.\n";
		cout << "그래도 사용하시겠습니까? (1. 예 / AnyKey. 아니오): ";

		int choice;
		cin >> choice;

		if (choice == 1) {
			character->SetHealth(remainingHealth);
		}
		else {
			cout << "포션 사용을 취소했습니다.\n";
			return false;
		}
	}
	else {
		character->SetHealth(mHealthRestore);
	}

	character->UseItem(0);	
	return true;
}

void HealthPotion::SellItem(Character* character)
{
	character->SetGold(nSellPrice); delete this;
}

void HealthPotion::printInfo()
{
	cout << mName << " | 회복량 : " << mHealthRestore << " | 판매가 : " << nSellPrice << endl;
}

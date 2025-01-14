#include "Weapon.h"
#include "Character.h"

void Weapon::Use(Character* character)
{
	// TODO : 무기 클래스 장착 이벤트 구현

}

void Weapon::SellItem(Character* character)
{
	character->SetGold(nSellPrice); delete this;
}

void Weapon::printInfo()
{
	cout << sName << " | 추가 공격력 : " << nExtraDamage << " | 장착 가능 레벨 : " << nEquipLevel << " | 판매가 : " << nSellPrice << endl;
}

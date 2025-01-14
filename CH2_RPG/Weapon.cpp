#include "Weapon.h"
#include "Character.h"

Weapon* Weapon::equippedWeapon = nullptr;

bool Weapon::Use(Character* character)
{
    if (character->GetLevel() < nEquipLevel) {
        cout << "레벨이 부족합니다. 요구 레벨: " << nEquipLevel << "\n";
        return false;
    }

    if (isEquipped) {
        // 장착 해제
        character->SetAttack(-nExtraDamage);
        isEquipped = false;
        equippedWeapon = nullptr;
        cout << sName << "을(를) 해제했습니다.\n";
        cout << "기본 공격력으로 돌아갑니다.\n";
        return true;
    }
    else {
        // 기존 무기 해제
        if (equippedWeapon) {
            equippedWeapon->Use(character); 
        }

        // 새 무기 장착
        character->SetAttack(nExtraDamage);
        isEquipped = true;
        equippedWeapon = this;
        cout << sName << "을(를) 장착했습니다.\n";
        cout << "공격력이 " << nExtraDamage << " 증가했습니다.\n";
        return true;
    }
}

void Weapon::SellItem(Character* character)
{
	character->SetGold(nSellPrice); delete this;
}

void Weapon::printInfo()
{
	cout << sName << " | 추가 공격력 : " << nExtraDamage << " | 장착 가능 레벨 : " << nEquipLevel << " | 판매가 : " << nSellPrice << endl;
}

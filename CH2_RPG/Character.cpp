#include <iostream>
#include "Character.h"
#include "Item.h"

Character* Character::instance = nullptr;

Character* Character::GetInstance(string name)
{
    if (instance == nullptr)
    {
        instance = new Character(name);
    }
    return instance;
}

void Character::DisplayStatus()
{
    cout << "캐릭터 이름: " << mName << "\n";
    cout << "레벨: " << mLevel << "\n";
    cout << "체력: " << mHealth << "\n";
    cout << "공격력: " << mAttack << "\n";
    cout << "처치한 몬스터 수: " << mTotalMonsterKills << "\n";
    cout << "골드: " << mGold << "\n";
}

void Character::LevelUp()
{
    //레벨 올려주고, 경험치 초기화
    mLevel++;
    mExperience = 0;

    if (mLevel >= maxLevel)
    {
        mLevel = maxLevel;
        mHealth = mMaxHealth;
        cout << "최대 레벨 도달! 더 이상 능력치 상승은 없습니다.\n";
        return;
    }

    cout << mName << " 레벨업!!\n";

    //health, attack 세팅
    mMaxHealth += mLevel * 20;
    mHealth = mMaxHealth;
    mAttack += mLevel * 5;
}

void Character::UseItem(int index)
{
    //health 포션
    if (index == 0)
    {
        cout << "체력 물약 사용! 현재 체력: " << mHealth << "\n";
    }
    //attack 포션
    else if (index == 1)
    {
        cout << "공격 부스터 사용! 현재 공격력: " << mAttack << "\n";
    }
}

//데미지 입을 때는 -값을넣어주어야함
void Character::SetHealth(int plusHealth)
{
    mHealth += plusHealth;
    if (mHealth <= 0)
        mHealth = 0;
    if (mHealth >= mMaxHealth)
        mHealth = mMaxHealth;
}

void Character::SetExperience(int exp)
{
    mExperience += exp;

    //level up
    if (mExperience >= maxExperience)
    {
        LevelUp();
    }
}

void Character::SetGold(int gold)
{
    mGold += gold;
}

void Character::SetInventory(Item* item)
{
    if (item)
    {
        mInventory.push_back(item);
        cout << item->GetName() << "획득!!\n";
    }
}

void Character::SetAttack(int attack)
{
    mAttack += attack;
}

void Character::SetTotalMonsterKills()
{
    mTotalMonsterKills++;
}

void Character::PopInventoryItem()
{
    mInventory.pop_back();
}


int Character::UseSkill(ABNOMAL_STATUS as)
{
    tSkillTable[as].iCooldown = tSkillTable[as].iCoolTime;

    return tSkillTable[as].iDuration;
}

void Character::SellItem(int idx)
{
    mInventory.erase(mInventory.begin() + idx);
}

//protected constructor
Character::Character(string name)
    :mName(name)
    , mLevel(1)
    , mHealth(200)
    , mMaxHealth(200)
    , mAttack(30)
    , mExperience(0)
    , mGold(0)
    , mTotalMonsterKills(0)
{
    if (name.empty())
    {
        mName = "player 0";
    }
}
#include <iostream>
#include <random>

#include "GameManager.h"
#include "RandomIntGenerator.h"
#include "Goblin.h"

#include "Slime.h"
#include "Orc.h"
#include "Troll.h"

#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

Monster* GameManager::GenerateMonster(int level)
{    
    int idx = GetRandomInt(0, mTotalMonsterCount);
    Monster* monster = nullptr;

    if (idx == 0)
        monster = new Goblin(level);
    else if (idx == 1)
        monster = new Orc(level);
    else if (idx == 2)
        monster = new Troll(level);
    else if (idx == 3)
        monster = new Slime(level);

    return monster;
}

bool GameManager::Battle(Character* player)
{
    Monster* monster = GenerateMonster(player->GetLevel());

    cout << "\n===================================\n\n";
    cout << "몬스터 " << monster->GetName() << " 등장! | 체력: "
        << monster->GetHealth() << " 공격력: " << monster->GetAttack() << "\n";


    //플레이어가 죽거나 몬스터가 죽거나
    while (1)
    {
        //player attack
        cout << player->GetName() << " 이(가) " << monster->GetName() << " 을(를) 공격합니다";
        monster->TakeDamage(player->GetAttack());
        cout << player->GetAttack() << " 데미지! "
            << monster->GetName() << " 체력: " << monster->GetHealth() << "\n";

        //monster death
        if (monster->GetHealth() == 0)
        {
            cout << monster->GetName() << " 이(가) 죽었습니다.\n";
            player->SetTotalMonsterKills();
            int golds = GetRandomInt(10, 20);
            cout << player->GetName() << " 이(가) 50EXP와 " << golds << " 골드를 획득했습니다.";    

            //item drop
            int itemDropProbability = GetRandomInt(1, 100);
            if (itemDropProbability <= 30)
            {                
                if (itemDropProbability <= 15)
                {
                    Item* item = new HealthPotion();
                    player->SetInventory(item);
                }
                else
                {
                    Item* item = new AttackBoost();
                    player->SetInventory(item);
                }
            }

            player->SetExperience(50);
            player->SetGold(golds);

            cout << "현재 EXP: " << player->GetExperience() << "/100, " << " 골드: " << player->GetGold() << "\n\n";
            cout << "===================================\n\n";

            system("pause");
            system("cls");

            return true;
        }

        //monster attack
        cout << monster->GetName() << " 이(가) " << player->GetName() << " 을(를) 공격합니다";
        player->SetHealth(-monster->GetAttack());
        cout << monster->GetAttack() << " 데미지! "
            << player->GetName() << " 체력: " << player->GetHealth() << "\n";

        //random item 발동
        int itemUsingProbability = GetRandomInt(1, 100);
        if (itemUsingProbability <= 30)
        {
            //비어있지 않다면, 
            if (!player->GetInventory().empty())
            {
                //아이템 사용
                Item* item = player->GetInventory().back();
                item->Use(player);
                player->PopInventoryItem();
            }
        }

        //player death
        if (player->GetHealth() == 0)
        {
            cout << player->GetName() << " 이(가) 죽었습니다.\n";
            cout << "게임 오버\n";     
                       
            return false;
        }
    }
}

void GameManager::DisplayInventory(Character* player)
{
    if (player->GetInventory().empty())
    {
        cout << "인벤토리가 비었습니다\n";              
    }
    else
    {
        for (const auto& item : player->GetInventory())
        {
            cout << item->GetName() << "\n";
        }
    }
}


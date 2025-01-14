#include <iostream>
#include <random>

#include "GameManager.h"

#include "BossMonster.h"
#include "Goblin.h"
#include "Slime.h"
#include "Orc.h"
#include "Troll.h"

#include "Shop.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

Monster* GameManager::GenerateMonster(int level)
{
    Monster* monster = nullptr;

    if (level == 10)
        monster = new BossMonster(level);
    else
    {
        int idx = GetRandomInt(0, mTotalMonsterCount);

        if (idx == 0)
            monster = new Goblin(level);
        else if (idx == 1)
            monster = new Orc(level);
        else if (idx == 2)
            monster = new Troll(level);
        else if (idx == 3)
            monster = new Slime(level);
    }

    return monster;
}

bool GameManager::Battle(Character* player)
{
    Monster* monster = GenerateMonster(player->GetLevel());
    int iMenu;

    while (1) {
        system("cls");
        cout << "\n===================================\n\n";
        cout << "몬스터 " << monster->GetName() << " 등장!\t| 체력: "
            << monster->GetHealth() << " 공격력: " << monster->GetAttack() << "\n";
        cout << "플레이어 : " << player->GetName() << "\t| "
            << "체력: " << player->GetHealth() << "\n\n";

        cout << "1. 공격\n";
        cout << "2. 스킬사용\n";
        cout << "3. 아이템 사용\n";
        cout << "0. 도망가기\n";
        cout << "메뉴를 선택하세요 : ";
        cin >> iMenu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }

        if (iMenu == BATTLE_BACK)
            return true;        

        cout << "\n\n";

        switch (iMenu) {
        case BATTEL_ATTACK:
            //player attack
            cout << player->GetName() << " 이(가) " << monster->GetName() << " 을(를) 공격합니다. ";
            monster->TakeDamage(player->GetAttack());
            cout << player->GetAttack() << " 데미지! "
                << monster->GetName() << " 체력: " << monster->GetHealth() << "\n";

            //monster death
            if (MonsterDeadCheck(player, monster))
                return true;

            break;

        case BATTLE_SKILL:
            // player use skill
            system("cls");
            cout << "\n===================================\n\n";
            cout << "몬스터 " << monster->GetName() << " 등장! | 체력: "
                << monster->GetHealth() << " 공격력: " << monster->GetAttack() << "\n\n";

            if (player->GetLevel() >= 3)
                cout << "1. 마비\n";
            if (player->GetLevel() >= 6)
                cout << "2. 출혈\n";
            if (player->GetLevel() >= 9)
                cout << "3. 혼란\n";
            cout << "0. 뒤로가기\n";
            cout << "메뉴를 선택하세요 : ";
            cin >> iMenu;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1024, '\n');
                continue;
            }

            if (iMenu == 0)
                continue;

            switch (iMenu) {
            case 1:
                // player use shock
                if (player->GetLevel() >= 3) {
                    if (player->tSkillTable[AS_SHOCK].iCooldown == 0) {
                        cout << player->GetName() << " 이(가) " << monster->GetName() << " 에게 마비 스킬을 사용합니다.!\n";
                        monster->TakeDamage(player->tSkillTable[AS_SHOCK].iDamage);
                        monster->ASCheck[AS_SHOCK] = player->UseSkill(AS_SHOCK);
                        cout << player->tSkillTable[AS_SHOCK].iDamage << " 데미지! "
                            << monster->GetName() << " 체력: " << monster->GetHealth() << "\n";
                    }
                    else {
                        cout << "해당 스킬은 " << player->tSkillTable[AS_SHOCK].iCooldown << " 이후 사용이 가능합니다.\n";
                        system("pause");
                        continue;
                    }
                }

                break;

            case 2:
                // player use bleeding
                if (player->GetLevel() >= 6) {
                    if (player->tSkillTable[AS_BLEEDING].iCooldown == 0) {
                        cout << player->GetName() << " 이(가) " << monster->GetName() << " 에게 출혈 스킬을 사용합니다.!\n";
                        monster->TakeDamage(player->tSkillTable[AS_BLEEDING].iDamage);
                        monster->ASCheck[AS_BLEEDING] = player->UseSkill(AS_BLEEDING);
                        cout << player->tSkillTable[AS_BLEEDING].iDamage << " 데미지! "
                            << monster->GetName() << " 체력: " << monster->GetHealth() << "\n";
                    }
                    else {
                        cout << "해당 스킬은 " << player->tSkillTable[AS_BLEEDING].iCooldown << " 이후 사용이 가능합니다.\n";
                        system("pause");
                        continue;
                    }
                }

                break;

            case 3:
                // player use disarray
                if (player->GetLevel() >= 9) {
                    cout << player->GetName() << " 이(가) " << monster->GetName() << " 에게 혼란 스킬을 사용합니다.!\n";
                    monster->ASCheck[AS_DISARRAY] = player->UseSkill(AS_DISARRAY);
                }
                else {
                    cout << "해당 스킬은 " << player->tSkillTable[AS_DISARRAY].iCooldown << " 이후 사용이 가능합니다.\n";
                    system("pause");
                    continue;
                }

                break;

            }

            break;

        case BATTLE_USEITEM:
            // player use item
            vector<Item*> usableItems;
            for (Item* item : player->GetInventory()) {
                if (dynamic_cast<Weapon*>(item) == nullptr) {
                    usableItems.push_back(item);
                }
            }

            if (usableItems.empty()) {
                cout << "사용 가능한 아이템이 없습니다.\n";
                system("pause");
                continue;
            }

            cout << "0. 뒤로가기\n";
            for (size_t i = 0; i < usableItems.size(); ++i) {
                cout << i + 1 << ". ";
                usableItems[i]->printInfo();
            }
            cout << "사용할 아이템 번호를 선택하세요: ";

            int itemChoice;
            cin >> itemChoice;

            if (cin.fail() || itemChoice < 0 || itemChoice > usableItems.size()) {
                cin.clear();
                cin.ignore(1024, '\n');
                continue;
            }

            if (itemChoice == 0) {
                continue;
            }

            int actualIndex = -1;
            Item* selectedItem = usableItems[itemChoice - 1];

            for (int i = 0; i < player->GetInventory().size(); ++i) {
                if (player->GetInventory()[i] == selectedItem) {
                    actualIndex = i;
                    break;
                }
            }

            if (actualIndex != -1) {
                bool itemUsed = selectedItem->Use(player);
                if (itemUsed) {
                    player->SellItem(actualIndex);
                    break;
                }
                
                system("pause");
                continue;
            }

            system("pause");
            break;
        }

        // monster attack
        // monster bleeding check
        if (monster->ASCheck[AS_BLEEDING] > 0) {
            cout << monster->GetName() << " 이(가) 현재 출혈상태 입니다.\n";
            monster->ASCheck[AS_BLEEDING]--;
            monster->TakeDamage(player->GetAttack() / 5);
            cout << monster->GetName() << " 에게 출혈 " << player->GetAttack() / 5 << " 데미지!"
                << monster->GetName() << " 체력 : " << monster->GetHealth() << "\n";

            if (MonsterDeadCheck(player, monster))
                return true;
        }

        // monster shock check
        if (monster->ASCheck[AS_SHOCK] > 0) {
            cout << monster->GetName() << " 이(가) 현재 마비상태 입니다.\n";
            monster->ASCheck[AS_SHOCK]--;
            int idx = GetRandomInt(0, 1);

            if (idx == 0) {
                cout << monster->GetName() << " 이(가) 마비로 인해 아무런 행동을 하지 못했습니다.\n";
            }
            else {
                // monster disarry check
                if (monster->ASCheck[AS_DISARRAY] > 0) {
                    cout << monster->GetName() << " 이(가) 현재 혼란상태 입니다.\n";

                    idx = GetRandomInt(0, 1);
                    if (idx == 0) {
                        cout << monster->GetName() << " 이(가) 실수로 자기자신을 때렸습니다.\n";
                        monster->TakeDamage(monster->GetAttack() / 2);
                        cout << monster->GetName() << " 에게 " << monster->GetAttack() / 2 << " 데미지!"
                            << monster->GetName() << " 체력 : " << monster->GetHealth() << "\n";
                    }
                    else {
                        cout << monster->GetName() << " 이(가) " << player->GetName() << " 을(를) 공격합니다. ";
                        player->SetHealth(-monster->GetAttack());
                        cout << monster->GetAttack() << " 데미지! "
                            << player->GetName() << " 체력: " << player->GetHealth() << "\n";
                    }
                }
                else {
                    cout << monster->GetName() << " 이(가) " << player->GetName() << " 을(를) 공격합니다. ";
                    player->SetHealth(-monster->GetAttack());
                    cout << monster->GetAttack() << " 데미지! "
                        << player->GetName() << " 체력: " << player->GetHealth() << "\n";
                }
            }
        }
        else {
            // monster disarry check
            if (monster->ASCheck[AS_DISARRAY] > 0) {
                cout << monster->GetName() << " 이(가) 현재 혼란상태 입니다.\n";

                int idx = GetRandomInt(0, 1);
                if (idx == 0) {
                    cout << monster->GetName() << " 이(가) 실수로 자기자신을 때렸습니다.\n";
                    monster->TakeDamage(monster->GetAttack() / 2);
                    cout << monster->GetName() << " 에게 " << monster->GetAttack() / 2 << " 데미지!"
                        << monster->GetName() << " 체력 : " << monster->GetHealth() << "\n";
                }
                else {
                    cout << monster->GetName() << " 이(가) " << player->GetName() << " 을(를) 공격합니다. ";
                    player->SetHealth(-monster->GetAttack());
                    cout << monster->GetAttack() << " 데미지! "
                        << player->GetName() << " 체력: " << player->GetHealth() << "\n";
                }
            }
            //[monster attack]
            else {
                cout << monster->GetName() << " 이(가) " << player->GetName() << " 을(를) 공격합니다. ";
                player->SetHealth(-monster->GetAttack());
                cout << monster->GetAttack() << " 데미지! "
                    << player->GetName() << " 체력: " << player->GetHealth() << "\n";

                //[boss skill attack]
                if (monster->GetName() == "Boss Monster")
                {
                    int skillProbability = GetRandomInt(1, 100);
                    if (skillProbability <= 40)
                    {
                        int skillDamage = static_cast<BossMonster*>(monster)->SkillAttackDamage();
                        cout << monster->GetName() << " 의 스킬 공격!";
                        player->SetHealth(-skillDamage);
                        cout << skillDamage << " 데미지! "
                            << player->GetName() << " 체력: " << player->GetHealth() << "\n";
                    }
                }
            }
        }

        //[monster death]
        if (MonsterDeadCheck(player, monster))
            return true;

        // [player death]
        if (PlayerDeadCheck(player))
            return false;       

        // player skill cooldown
        if (player->tSkillTable[AS_SHOCK].iCooldown > 0)
            player->tSkillTable[AS_SHOCK].iCooldown--;
        if (player->tSkillTable[AS_BLEEDING].iCooldown > 0)
            player->tSkillTable[AS_BLEEDING].iCooldown--;
        if (player->tSkillTable[AS_DISARRAY].iCooldown > 0)
            player->tSkillTable[AS_DISARRAY].iCooldown--;

        system("pause");
    }    
}

void GameManager::DisplayInventory(Character* player)
{
    cout << "\n[ 장착 중인 장비 ]\n";
    if (Weapon::GetEquippedWeapon()) {
        cout << "무기: ";
        Weapon::GetEquippedWeapon()->printInfo();
    }
    else {
        cout << "무기: (없음)\n";
    }

    cout << "\n[ 보유 아이템 ]\n";

    if (player->GetInventory().empty())
    {
        cout << "인벤토리가 비었습니다\n";
    }
    else
    {
        int idx = 0;
        for (auto item : player->GetInventory())
        {
            cout << ++idx << ". ";
            if (item == Weapon::GetEquippedWeapon()) {
                cout << "[장착중] ";
            }
            item->printInfo();
        }
    }
}

void GameManager::ManageInventory(Character* player)
{
    while (1) {
        system("cls");
        cout << "\n============인벤토리==================\n\n";
        DisplayInventory(player);

        cout << "\n===================================\n\n";
        cout << "1. 아이템 사용/해제  AnyKey. 상점 나가기" << endl;
        cout << "입력 : ";

        int input;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            return;
        }

        if (input == 1) {
            if (player->GetInventory().empty()) {
                cout << "인벤토리가 비었습니다.\n";
                system("pause");
                continue;
            }

            cout << "사용/해제할 아이템 번호를 입력하세요: ";
            cin >> input;

            if (input > 0 && input <= player->GetInventory().size()) {
                Item* selectedItem = player->GetInventory()[input - 1];
                Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);

                if (weapon) {
                    weapon->Use(player);
                }
                else {
                    bool itemUsed = selectedItem->Use(player);
                    if (itemUsed) {
                        player->SellItem(input - 1);
                    }
                }
                system("pause");
            }
        }
        else {
            return;
        }
    }
}

// 아이템 생성
Item* GameManager::GenerateWeapon(Character* player)
{
    Item* NewItem;
    
    int Lucky = GetRandomInt(1, 10) * player->GetLevel();

    // Drop quality based on player level
    if (Lucky < 20)
    {
        NewItem = new Weapon("나무 몽둥이", Lucky + GetRandomInt(-1, 1), 0);
    }
    else if (Lucky >= 20 && Lucky < 30)
    {
        NewItem = new Weapon("연습용 검", Lucky + GetRandomInt(-2, 2), 2);
    }
    else if (Lucky >= 30 && Lucky < 65)
    {
        NewItem = new Weapon("강철 도끼", Lucky + GetRandomInt(-3, 3), 5);
    }
    else
    {
        NewItem = new Weapon("엑스칼리버", Lucky + GetRandomInt(-4, 4), 8);
    }

    return NewItem;
}

void GameManager::GenerateShop()
{
    shop = new Shop();
}

// Open Shop
void GameManager::UseShop(Character* Player)
{
    int input;

OPEN_SHOP:
    system("cls");
    shop->DisplayItems(Player);

    cout << "1. 구매   2. 판매  3. 정보 보기  AnyKey. 상점 나가기" << endl;
    cout << "입력 : ";
    cin >> input;

    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(1024, '\n');     
    }

    switch (input)
    {
    case 1:
    BUY_ITEM:
        system("cls");
        shop->DisplayItems(Player);
        cout << "구매할 아이템 번호 : ";
        cin >> input;

        if (!cin || input < 1 || input > shop->GetItemCount())
        {
            cout << "잘못된 입력값입니다. 다시 입력해주세요." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            system("pause");
            goto BUY_ITEM;
        }
        shop->BuyItem(input - 1, Player);
        system("pause");
        goto OPEN_SHOP;
    case 2:
    SELL_ITEM:
        system("cls");
        DisplayInventory(Player);
        if (Player->GetInventory().size() == 0)
        {
            system("pause");
            goto OPEN_SHOP;
        }
        cout << "판매할 아이템 번호 : ";
        cin >> input;
        if (!cin || input < 1 || input > Player->GetInventory().size())
        {
            cout << "잘못된 입력값입니다. 다시 입력해주세요." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            system("pause");
            goto SELL_ITEM;
        }
        shop->SellItem(input - 1, Player);
        system("pause");
        goto OPEN_SHOP;
    case 3:
    PNT_INFO:
        system("cls");
        shop->DisplayItems(Player);
        cout << "정보를 확인하고 싶은 아이템 번호 : ";
        cin >> input;
        if (!cin || input < 1 || input > shop->GetItemCount())
        {
            cout << "잘못된 입력값입니다. 다시 입력해주세요." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            system("pause");
            goto PNT_INFO;
        }
        shop->GetInfo(input - 1);
        system("pause");
        goto OPEN_SHOP;
    default:
        break;
    }

    cout << "상점 이용을 종료합니다." << endl;
    system("pause");
    system("cls");
}

void GameManager::ResetShop(Character* Player)
{
    shop->ResetItems();

    for (int i = 0; i < WPN_ITEM; i++)
    {
        Item* item = GenerateWeapon(Player);        // Add random weapons based on player level
        shop->SetItems(item);
    }
}

bool GameManager::MonsterDeadCheck(Character* player, Monster* monster) {
    if (monster->GetHealth() == 0)
    {
        if (monster->GetName() == "Boss Monster")
        {
            cout << "\n===================================\n\n";
            cout << monster->GetName() << " 을(를) 처치했습니다!!\n";
            cout << "게임 클리어!\n";
            cout << "\n===================================\n";

            GameOverFlag = true;
            return true;
        }

        cout << monster->GetName() << " 이(가) 죽었습니다.\n";
        player->SetTotalMonsterKills();
        int golds = GetRandomInt(10, 20);
        cout << player->GetName() << " 이(가) 50EXP와 " << golds << " 골드를 획득했습니다. ";

        //item drop
        int itemDropProbability = GetRandomInt(1, 100);
        if (itemDropProbability <= 30)
        {
            Item* item;
            if (itemDropProbability <= 13)                  
            {
                item = new HealthPotion();
                player->SetInventory(item);
            }
            else if(itemDropProbability > 13 && itemDropProbability <= 26)
            {
                item = new AttackBoost();
                player->SetInventory(item);
            }
            else
            {
                item = GenerateWeapon(player);
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

    return false;
}

bool GameManager::PlayerDeadCheck(Character* player)
{
    if (player->GetHealth() == 0)
    {
        cout << "\n===================================\n\n";
        cout << player->GetName() << " 이(가) 죽었습니다.\n";
        cout << "게임 오버\n";
        cout << "\n===================================\n";

        return true;
    }

    return false;
}

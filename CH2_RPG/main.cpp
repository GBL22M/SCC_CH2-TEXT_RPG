#include <iostream>
#include <windows.h>
#include "GameManager.h"
#include "Character.h"

using namespace std;

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gameManager;

	cout << "================ TEXT RPG ================\n";
	cout << "캐릭터 이름을 입력하세요: ";
	string name;
	getline(cin, name);
	
	Character* character = Character::GetInstance(name);
	cout << "\n캐릭터 생성 완료!\n";
	character->DisplayStatus();
	cout << "모험을 시작합니다\n";
	system("pause");
	system("cls");
	
	//종료 조건
	while (1)
	{		
		cout << "\n============STATUS==================\n\n";
		character->DisplayStatus();
		cout << "\n===================================\n\n";
		cout << "1: 전투\n";
		cout << "2: 인벤토리\n";
		cout << "3: 상점\n";
		cout << "0: 게임 종료\n";
		cout << "\n===================================\n";
		cout << "원하는 메뉴를 입력하세요: ";

		string choice;
		getline(cin, choice);
		
		system("cls");

		if (choice == "1")
		{
			//monster 처치
			if (gameManager.Battle(character))
			{
				
			}
			//game 종료
			else
			{
				return 0;
			}			
		}
		else if (choice == "2")
		{
			//인벤토리
			system("cls");
			cout << "\n============INVENTORY==================\n\n";
			gameManager.DisplayInventory(character);	
			cout << "\n===================================\n\n";
			system("pause");
			system("cls");
		}
		else if (choice == "3")
		{
			//상점
		}
		else if (choice == "0")
		{
			cout << "게임 종료!\n";
			return 0;
		}
		else
		{			
			while (choice != "1" && choice != "2" && choice != "3" && choice == "0")
			{				
				cout << "올바른 숫자를 입력하세요: ";
				getline(cin, choice);
			}
		}		
	}
}
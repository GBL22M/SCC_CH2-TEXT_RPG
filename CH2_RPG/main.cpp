#include <iostream>
#include <windows.h>
#include "GameManager.h"
#include "Character.h"

using namespace std;

int main()
{
	GameManager gameManager;

	cout << "================ TEXT RPG ================\n";
	cout << "ĳ���� �̸��� �Է��ϼ���: ";
	string name;
	getline(cin, name);

	Character* character = Character::GetInstance(name);
	cout << "\nĳ���� ���� �Ϸ�!\n";
	character->DisplayStatus();
	cout << "������ �����մϴ�\n";
	system("pause");
	system("cls");

	//���� ����
	while (1)
	{
		cout << "\n============STATUS==================\n\n";
		character->DisplayStatus();
		cout << "\n===================================\n\n";
		cout << "1: ����\n";
		cout << "2: �κ��丮\n";
		cout << "3: ����\n";
		cout << "0: ���� ����\n";
		cout << "\n===================================\n";
		cout << "���ϴ� �޴��� �Է��ϼ���: ";

		string choice;
		getline(cin, choice);

		system("cls");

		if (choice == "1")
		{
			//monster óġ
			if (gameManager.Battle(character))
			{

			}
			//game ����
			else
			{
				return 0;
			}
		}
		else if (choice == "2")
		{
			//�κ��丮
			system("cls");
			cout << "\n============INVENTORY==================\n\n";
			gameManager.DisplayInventory(character);
			cout << "\n===================================\n\n";
			system("pause");
			system("cls");
		}
		else if (choice == "3")
		{
			//����
			system("cls");
			gameManager.UseShop(character);
		}
		else if (choice == "0")
		{
			cout << "���� ����!\n";
			return 0;
		}
		else
		{
			while (choice != "1" && choice != "2" && choice != "3" && choice == "0")
			{
				cout << "�ùٸ� ���ڸ� �Է��ϼ���: ";
				getline(cin, choice);
			}
		}
	}
}
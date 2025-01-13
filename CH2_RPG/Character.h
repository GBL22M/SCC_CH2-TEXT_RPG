#pragma once
#include <string>
#include <vector>
using namespace std;

class Item;

class Character
{
public:
	Character(const Character& other) = delete;
	Character& operator=(const Character&) = delete;

	static Character* GetInstance(string name);

	void DisplayStatus();
	void LevelUp();
	void UseItem(int index); 

	//getter
	int GetLevel() { return mLevel; }
	int GetHealth() { return mHealth; }
	int GetAttack() { return mAttack; }
	int GetExperience() { return mExperience; }
	int GetGold() { return mGold; }
	string GetName() { return mName; }
	vector<Item*>GetInventory() { return mInventory; }

	//setter
	void SetHealth(int damage);
	void SetExperience(int exp);
	void SetGold(int gold);
	void SetInventory(Item* item);
	void SetAttack(int attack);
	void SetTotalMonsterKills();
	void PopInventoryItem();

	void SellItem(int idx);

protected:
	Character(string name);

private:
	static Character* instance;
	string mName;
	int mLevel;
	int mHealth;
	int mMaxHealth;
	int mAttack;
	int mExperience;
	int mGold;
	int mTotalMonsterKills;
	vector<Item*> mInventory;	

	//
	const int maxExperience = 100;
	const int maxLevel = 10;
};
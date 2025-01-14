#pragma once

#include "Item.h"
#include "RandomIntGenerator.h"

class Weapon : public Item
{
public:
	Weapon(string NewName, int NewExtraDamage, int NewEquipLevel = 1)
		: sName(NewName), nExtraDamage(NewExtraDamage), nEquipLevel(NewEquipLevel)
	{
		nBuyPrice = GetRandomInt((int)(nExtraDamage * 1.7), nExtraDamage * 2);
		nSellPrice = (int)(nBuyPrice * 0.7);
	}
	string GetName() override { return sName; }
	void Use(Character* character) override;

	// Price Section
	int GetBuyPrice() { return nBuyPrice; }
	int GetSellPrice() { return nSellPrice; }
	void SetPrice(int NewBuyPrice) { nBuyPrice = NewBuyPrice; nSellPrice = (int)(nBuyPrice * 0.7); }

	// Sell Section
	void SellItem(Character* character) override;

	// Information Section
	void printInfo() override;
	static Weapon* GetEquippedWeapon() { return equippedWeapon; }
	bool IsEquipped() const { return isEquipped; }

private:
	string sName;
	int nExtraDamage;
	int nEquipLevel;
	int nBuyPrice;
	int nSellPrice;

	bool isEquipped = false;
	static Weapon* equippedWeapon;
};


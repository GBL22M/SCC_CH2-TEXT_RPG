#pragma once
#include "Item.h"

class HealthPotion : public Item
{
public:
	HealthPotion();
	string GetName() override;
	bool Use(Character* character) override;

	// Price Section
	int GetBuyPrice() override { return nBuyPrice; }
	int GetSellPrice() override { return nSellPrice; }

	// Sell Section
	void SellItem(Character* character) override;

	// Information Section
	void printInfo() override;

private:
	string mName;
	int mHealthRestore;
	int nBuyPrice;
	int nSellPrice;
};
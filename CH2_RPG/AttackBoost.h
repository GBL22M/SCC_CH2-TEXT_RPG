#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
	AttackBoost();
	string GetName() override;
	void Use(Character* character) override;

	// Price Section
	int GetBuyPrice() override { return nBuyPrice; }
	int GetSellPrice() override { return nSellPrice; }

	// Sell Section
	void SellItem(Character* character) override;

	// Information Section
	void printInfo() override;

private:
	string mName;
	int mAttackIncrease;
	int nBuyPrice;
	int nSellPrice;
};
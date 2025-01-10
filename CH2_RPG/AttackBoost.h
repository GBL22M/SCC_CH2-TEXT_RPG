#pragma once
#include "Item.h"

class AttackBoost : public Item
{
public:
	AttackBoost();
	string GetName() override;
	void Use(Character* character) override;

private:
	string mName;
	int mAttackIncrease;
};
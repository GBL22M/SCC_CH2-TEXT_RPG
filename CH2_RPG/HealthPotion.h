#pragma once
#include "Item.h"

class HealthPotion : public Item
{
public:
	HealthPotion();
	string GetName() override;
	void Use(Character* character) override;

private:
	string mName;
	int mHealthRestore;
};
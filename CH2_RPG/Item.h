#pragma once

#include <string>
#include <iostream>

using namespace std;

class Character;

class Item
{
public:
	virtual string GetName() = 0;
	virtual void Use(Character* character) = 0;
	virtual int GetBuyPrice() = 0;
	virtual int GetSellPrice() = 0;
	virtual void SellItem(Character* character) = 0;
	virtual void printInfo() = 0;
};
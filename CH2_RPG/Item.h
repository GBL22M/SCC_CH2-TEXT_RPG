#pragma once

#include <string>

using namespace std;

class Character;

class Item
{
public:
	virtual string GetName() = 0;
	virtual void Use(Character* character) = 0;
};
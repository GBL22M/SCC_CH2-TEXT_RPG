#pragma once

#include <string>
using namespace std;

class Monster
{
public:	
	virtual string GetName() = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual void TakeDamage(int damage) = 0;
};
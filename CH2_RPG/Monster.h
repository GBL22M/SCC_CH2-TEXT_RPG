#pragma once

#include <string>
#include <map>
#include "Skill.h"

using namespace std;

class Monster
{
public:
	map<ABNOMAL_STATUS, int> ASCheck =
	{ {AS_SHOCK, 0}, {AS_BLEEDING, 0}, {AS_DISARRAY, 0} };

public:
	virtual string GetName() = 0;
	virtual int GetHealth() = 0;
	virtual int GetAttack() = 0;
	virtual void TakeDamage(int damage) = 0;	
};
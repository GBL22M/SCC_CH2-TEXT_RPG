#pragma once

enum ABNOMAL_STATUS {
	AS_SHOCK,
	AS_BLEEDING,
	AS_DISARRAY,
	AS_END
};

struct _tagSkill {
	int iDamage;
	int iUseLevel;
	int iDuration;
	int iCooldown;
	int iCoolTime;
	ABNOMAL_STATUS asType;
};
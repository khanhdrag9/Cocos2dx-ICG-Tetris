#pragma once

#include "cocos2d.h"
#include <vector>

enum TypeChanges {
	O = 1,
	I,
	T,
	L,
	Z
};

class Changes
{

public:
	Changes(int type = 1);
	virtual ~Changes();

	int _type;
	
	void Init(unsigned int type = 0);
	std::vector<cocos2d::Vec2> _listRatioPos;
	cocos2d::Vec2 _ratioRotate;
};


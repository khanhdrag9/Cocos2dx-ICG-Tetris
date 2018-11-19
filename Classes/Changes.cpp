#include "Changes.h"

Changes::Changes(int type):
	_type(type)
{
	Init(type);
}

Changes::~Changes()
{
	_listRatioPos.clear();
}

void Changes::Init(unsigned int type)
{
	if (type != 0)_type = type;
	_listRatioPos.clear();

	switch (_type)
	{
	case TypeChanges::SQUARE:
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(2, 1),
			cocos2d::Vec2(1, 2),
			cocos2d::Vec2(2, 2)
		};

		break;
	case TypeChanges::LINE:
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(1, 2),
			cocos2d::Vec2(1, 3),
			cocos2d::Vec2(1, 4)
		};

		_ratioRotate = cocos2d::Vec2(1, -1);
		break;
	case TypeChanges::TRIANGLE:
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(2, 1),
			cocos2d::Vec2(2, 2),
			cocos2d::Vec2(3, 1)
		};
		break;
	case TypeChanges::L:
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(2, 1),
			cocos2d::Vec2(1, 2),
			cocos2d::Vec2(1, 3)
		};
		break;
	case TypeChanges::Z:
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(1, 2),
			cocos2d::Vec2(2, 2),
			cocos2d::Vec2(2, 3)
		};
		break;
	default:
		//default is Square
		_listRatioPos = {
			cocos2d::Vec2(1, 1),
			cocos2d::Vec2(2, 1),
			cocos2d::Vec2(1, 2),
			cocos2d::Vec2(2, 2)
		};
		break;
	}
}
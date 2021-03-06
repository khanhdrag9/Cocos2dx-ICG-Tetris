#pragma once

#include "cocos2d.h"
#include "Changes.h"
#include <vector>

enum typeMoves {
	FALL = 1,
	TOSIDE,
	ROTATE
};

enum directionRotate {
	LEFT = 1,
	RIGHT
};

class Shapes
{
public:
	Shapes();
	Shapes(float side, Changes* form);
	virtual ~Shapes();

	void setShape(float side = 0.f, Changes* form = nullptr);
	void setLayer(cocos2d::Layer* layer);

	//action trans
	void Rotate(cocos2d::Layer* layer, int direction = directionRotate::RIGHT);
	void MoveBy(cocos2d::Vec2 pos, bool useAction = false);

	std::vector<cocos2d::Sprite*> _listTitles;
	Changes* _form = nullptr;
};


#include "Shapes.h"
#include "Defines.h"

USING_NS_CC;

Shapes::Shapes()
{
	setShape();
}

Shapes::Shapes(float side, Changes* form)
{
	setShape(side, form);
}

Shapes::~Shapes()
{
	for (auto x : _listTitles)
		if (x)
			CC_SAFE_DELETE(x);
	_listTitles.clear();
}

void Shapes::setShape(float side, Changes* form)
{
	if (form == nullptr)
	{
		form = new Changes();
	}
	auto sz = cocos2d::Director::getInstance()->getVisibleSize();

	for (int i = 0; i < form->_listRatioPos.size(); i++)
	{
		auto title = Sprite::create(TITLE_PATH);

		if (side != 0)
		{
			auto ratioScale = side / (float)title->getBoundingBox().size.width;
			title->setScale(ratioScale);
		}
		//title->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
		if (i != 0)
		{
			auto titlePrevious = _listTitles[i - 1];
			auto ratioPos = form->_listRatioPos[i] - form->_listRatioPos[i - 1];
			auto sizePreviousTitle = titlePrevious->getBoundingBox().size;
			auto posPreviousTitle = titlePrevious->getPosition();
			
			title->setPosition(posPreviousTitle + Vec2(sizePreviousTitle.width * ratioPos.x, sizePreviousTitle.width * ratioPos.y));
		}
		else
		{
			int minX = title->getBoundingBox().size.width * 0.5f;
			title->setPosition(minX, sz.height + title->getBoundingBox().size.height);
		}
		
		//auto actionFall = MoveBy::create(SPEED_FALL, Vec2(0, -sz.height));
		//actionFall->setTag(typeMoves::FALL);
		//title->runAction(actionFall);
		_listTitles.push_back(title);
	}
}

void Shapes::MoveBy(cocos2d::Vec2 pos, bool useAction)
{
	for (auto x : _listTitles)
	{
		if (x)
		{
			if (useAction)
			{
				if (x->getNumberOfRunningActionsByTag(typeMoves::TOSIDE) == 0)
				{
					auto action = MoveBy::create(SPEED_MOVE, pos);
					x->runAction(action);
					
				}
			}
			else
			{
				x->setPosition(x->getPosition() + pos);
			}
		}
	}
}

void Shapes::Rotate()
{
	for (auto x : _listTitles)
	{

	}
}

void Shapes::setLayer(cocos2d::Layer* layer)
{
	for (auto x : _listTitles)
		if (x)
			layer->addChild(x, 2);
}
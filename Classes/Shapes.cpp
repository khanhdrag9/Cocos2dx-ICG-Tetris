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
		{
			CC_SAFE_DELETE(x);
		}
	_listTitles.clear();
}

void Shapes::setShape(float side, Changes* form)
{
	if (form == nullptr)
	{
		if(_form == nullptr)
			_form = new Changes();
	}
	else
	{
		_form = form;
	}

	auto sz = cocos2d::Director::getInstance()->getVisibleSize();

	for (int i = 0; i < _form->_listRatioPos.size(); i++)
	{
		auto title = Sprite::create(TITLE_PATH);

		if (side != 0)
		{
			auto ratioScale = side / (float)title->getBoundingBox().size.width;
			title->setScale(ratioScale);
		}
		
		//add code create postion for each sprite

		_listTitles.push_back(title);
	}
}

void Shapes::Update(float dt)
{
	//code logic for shape
}

void Shapes::Rotate(cocos2d::Layer* layer, int direction)
{
	if (_form)
	{
		
	}
}


void Shapes::MoveBy(const cocos2d::Vec2& pos)
{
	for (auto x : _listTitles)
	{
		if (x)
		{
			if (!_isRunning)
			{
				_target = pos;
			}
		}
	}
}

void Shapes::setLayer(cocos2d::Layer* layer)
{
	for (auto x : _listTitles)
		if (x)
			layer->addChild(x, 2);
}
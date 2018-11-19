#include "GamePlay.h"
#include "Defines.h"
#include <map>

USING_NS_CC;

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
	for (auto x : _listTitles) if (x) { CC_SAFE_DELETE(x); }
	for (auto x : _listChanges) if (x) { CC_SAFE_DELETE(x); }
}

Scene* GamePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlay::create();
	scene->addChild(layer);

    return scene;
}

bool GamePlay::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(NULL));

	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	createColumns();
	createChanges();
	createShapeFalling();

	//change background color after 0.5s	
	this->scheduleOnce(schedule_selector(GamePlay::setBlackColorBackground), 0.5);
	this->scheduleUpdate();

	//for touch
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegin, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMove, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);


    return true;
}

void GamePlay::update(float)
{
	CheckCollision();
	if(_shapeFalling)
	{
		_shapeFalling->MoveBy(Vec2(0, -SPEED_FALL));
	}
}

void GamePlay::createColumns()
{
	_sideTitle = _screenSize.width / (float)NUMBER_COLUMN;
	float firstX = _sideTitle / 2.f;
	float firstY= _sideTitle / 2.f;

	for (int i = 0; i < NUMBER_COLUMN; i++)
	{
		_listColumn.push_back(Vec2(firstX, firstY));

		firstX += _sideTitle;
	}

}

void GamePlay::createChanges()
{
	for (int i = 1; i <= 5; i++)
	{
		_listChanges.push_back(new Changes(i));
	}
}

bool checkColistion2Rect(const cocos2d::Vec2& posA, const cocos2d::Vec2& posB, const cocos2d::Size& sizeA, const cocos2d::Size& sizeB)
{
	float rangeX = abs(posA.x - posB.x);
	float rangeY = abs(posA.y - posB.y);

	if (rangeX < ((sizeA.width + sizeB.width) * 0.5) &&
		rangeY <= ((sizeA.height + sizeB.height) * 0.5))
	{
		return true;
	}
	return false;
}

bool GamePlay::CheckCollision()
{
	bool isCollision = false;
	for (auto sprite : _shapeFalling->_listTitles)
	{
		//with bottom edge
		if (sprite->getPositionY() <= sprite->getBoundingBox().size.height * 0.5f)
		{
			//sprite->stopAllActionsByTag(typeMoves::ROTATE);
			//sprite->setPositionY(sprite->getBoundingBox().size.height * 0.5f);
			
			for (auto x : _shapeFalling->_listTitles)
			{
				_listTitles.push_back(x);
			}

			checkTitleFill();

			isCollision = true;
			_shapeFalling = nullptr;
			createShapeFalling();
			return isCollision;
		}

		for (auto title : _listTitles)
		{
			if (checkColistion2Rect(sprite->getPosition(), title->getPosition(), sprite->getBoundingBox().size, title->getBoundingBox().size))
			{
				for (auto x : _shapeFalling->_listTitles)
				{
					_listTitles.push_back(x);
				}

				checkTitleFill();

				isCollision = true;
				_shapeFalling = nullptr;
				createShapeFalling();
				return isCollision;
			}
		}
		
	}
	return isCollision;
}

bool GamePlay::checkTitleFill()
{
	int count = 0;
	std::map<float, int> numberVec;
	for(auto x : _listTitles)
	{
		if(numberVec[x->getPositionY()])
		{
			numberVec[x->getPositionY()]++;
		}
		else
		{
			numberVec[x->getPositionY()] = 1;
		}
	}

	//remove title ok
	for (auto x : numberVec)
	{
		if (x.second == NUMBER_COLUMN)
		{
			for (int i = 0; i < _listTitles.size();)
			{
				if (_listTitles[i]->getPositionY() == x.first)
				{
					this->removeChild(_listTitles[i]);
					_listTitles[i]->release();
					//CC_SAFE_DELETE(_listTitles[i]);
					_listTitles.erase(_listTitles.begin() + i);
				}
				else
					i++;
			}
			//down all title above
			for (auto tabove : _listTitles)
			{
				if (tabove->getPositionY() >= x.second + _sideTitle)
				{
					auto actionDown = MoveBy::create(SPEED_MOVE * 2.f, Vec2(0, -_sideTitle));
					actionDown->setTag(typeMoves::FALL);
					tabove->runAction(actionDown);
				}
			}
		}	
	}

	return true;
}

void GamePlay::createShapeFalling()
{
	int type = rand() % 5;
	CCLOG("type falling : %d", type);

	type = 1;
	_shapeFalling = new Shapes(_sideTitle, _listChanges[type]);

	int ranX = rand() % (NUMBER_COLUMN - 3 - 4) + 4;
	_shapeFalling->MoveBy(Vec2(ranX * _sideTitle, 0));

	_shapeFalling->setLayer(this);
}

bool GamePlay::onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_touchBegin = touch->getLocation();

	return true;
}

void GamePlay::onTouchMove(Touch* touch, Event* event)
{

}

void GamePlay::onTouchRelease(Touch* touch, Event* event)
{
	if (_shapeFalling)
	{
		auto posRelease = touch->getLocation();
		float subXOf2Pos = posRelease.x - _touchBegin.x;
		if (abs(subXOf2Pos) > abs(posRelease.y - _touchBegin.y))
		{
			Vec2 moveByPos;
			if (posRelease.x > _touchBegin.x)
			{
				moveByPos = Vec2(_sideTitle, 0);
			}
			else if (posRelease.x < _touchBegin.x)
			{
				moveByPos = Vec2(-_sideTitle, 0);
			}

			//check collistion with title near it
			for (auto x : _shapeFalling->_listTitles)
			{
				for (auto title : _listTitles)
				{
					if (abs(title->getPositionX() - x->getPositionX()) == _sideTitle)
					{
						if (checkColistion2Rect(title->getPosition(), x->getPosition() + moveByPos, title->getBoundingBox().size, x->getBoundingBox().size))
							return;
					}
				}
			}

			//end check

			_shapeFalling->MoveBy(moveByPos, true);
		}
		else
		{
			if (subXOf2Pos > 0)
			{
				_shapeFalling->Rotate(this, directionRotate::RIGHT);
			}
			else
			{
				_shapeFalling->Rotate(this, directionRotate::LEFT);
			}
		}
	}
}


void GamePlay::setBlackColorBackground(float)
{
	Director::getInstance()->setClearColor(Color4F::BLACK);
}

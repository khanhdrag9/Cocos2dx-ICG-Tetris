#include "GamePlay.h"
#include "Defines.h"
#include <map>

USING_NS_CC;

GamePlay::GamePlay():
	_sideTitle(0.f)
{

}

GamePlay::~GamePlay()
{
	for (auto x : _listTitles) if (x) { CC_SAFE_DELETE(x); }
	for (auto x : _listChanges) if (x) { CC_SAFE_DELETE(x); }
	_listColumn.clear();
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
	
}

void GamePlay::createColumns()
{
	

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
	

	return isCollision;
}

bool GamePlay::checkTitleFill()
{
	

	return true;
}

void GamePlay::createShapeFalling()
{
	//random type of shapes
	int type = rand() % 5;
	CCLOG("type falling : %d", type);

	
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
	
}


void GamePlay::setBlackColorBackground(float)
{
	Director::getInstance()->setClearColor(Color4F::BLACK);
}

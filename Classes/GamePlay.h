#pragma once

#include "cocos2d.h"
#include "Shapes.h"
#include <vector>

class GamePlay : public cocos2d::Layer
{
	Shapes* _shapeFalling;
	std::vector<cocos2d::Sprite*> _listTitles;
	std::vector<Changes*> _listChanges;
	std::vector<cocos2d::Vec2> _listColumn;

	cocos2d::Size _screenSize;
	cocos2d::Vec2 _origin;

	float _sideTitle;

	cocos2d::Vec2 _touchBegin;

	void createColumns();
	void createChanges();
	bool CheckCollision();
	void createShapeFalling();
	bool checkTitleFill();
public:
	GamePlay();
	virtual ~GamePlay();
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float) override;
        
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

	void setBlackColorBackground(float);

	bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMove(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchRelease(cocos2d::Touch* touch, cocos2d::Event* event);

};


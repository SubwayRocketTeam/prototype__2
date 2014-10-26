#pragma once

#include "cocos2d.h"

class Player;

class GameScene : public cocos2d::Layer{
public:
	CREATE_FUNC(GameScene);
    virtual bool init();  

    static cocos2d::Scene* scene();

private:
	Player *player;
};

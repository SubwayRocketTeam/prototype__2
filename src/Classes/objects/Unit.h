#pragma once

#include "cocos2d.h"

#include <string>

class Unit : public cocos2d::Sprite{
public:
	enum ActionType{
		actionMove,
		actionAttack,
		actionFocus,
	};
	enum CollisionChannel{
		channelPlayer = 0x0000000F,
		channelBullet = 0x000000F0,
		channelEnemy = 0x00000F00,
	};

public:
	static Unit *create();
	static Unit *create(
		const std::string &image);

    virtual bool init();
	virtual bool init(
		const std::string &image);

protected:
	Unit();
	virtual ~Unit();

	virtual bool initPhysics();

protected:
	cocos2d::Sprite *body;
};

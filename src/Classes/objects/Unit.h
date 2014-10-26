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

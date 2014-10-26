#pragma once

#include "cocos2d.h"

class MouseEventListener{
protected:
	MouseEventListener();
	virtual ~MouseEventListener();

	void enableMouseInput(
		cocos2d::Node *target);
	void disableMouseInput();

	virtual void onMouseMove(
		cocos2d::EventMouse *e);
	virtual void onMouseDown(
		cocos2d::EventMouse *e);
	virtual void onMouseUp(
		cocos2d::EventMouse *e);

private:
	cocos2d::Node *target;
	cocos2d::EventListenerMouse *mouseListener;
};

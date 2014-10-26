#include "MouseEventListener.h"

using namespace cocos2d;

MouseEventListener::MouseEventListener() :
	mouseListener(nullptr){
}
MouseEventListener::~MouseEventListener(){
}

void MouseEventListener::enableMouseInput(
	Node *target){

	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event *e){
		onMouseMove((EventMouse*)e);
	};
	mouseListener->onMouseUp = [this](Event *e){
		onMouseDown((EventMouse*)e);
	};
	mouseListener->onMouseDown = [this](Event *e){
		onMouseUp((EventMouse*)e);
	};

	target->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(mouseListener, target);
}
void MouseEventListener::disableMouseInput(){
	if(mouseListener){
		target->getEventDispatcher()->
			removeEventListener(mouseListener);
	}
}

void MouseEventListener::onMouseMove(
	EventMouse *e){

	cocos2d::log("onMouseMove : override me");
}
void MouseEventListener::onMouseDown(
	EventMouse *e){

	cocos2d::log("onMouseDown : override me");
}
void MouseEventListener::onMouseUp(
	EventMouse *e){

	cocos2d::log("onMouseUp : override me");
}
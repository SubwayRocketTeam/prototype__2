#include "Player.h"

#include "EnemyPool.h"
#include "Bullet.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

using namespace std;
using namespace cocos2d;

Player::Player() : 
	speed(4){
}
Player::~Player(){
}

Player *Player::create(){
	Player *p = new Player();
	
	if(p && p->init()){
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Player::init(){
	if (!Unit::init(R::PlayerBody))
        return false; 

	enableMouseInput(this);
	enableKeyboardInput(this);

	lay = DrawNode::create();
	addChild(lay);

    return true;
}
bool Player::initPhysics(){
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("player");

	if(pbody){
		setPhysicsBody(pbody);
		return true;
	}
	
	return false;
}

void Player::processRotation(
	float x,float y){

	auto screenSize = Director::getInstance()->getWinSize();
	Vec2 center =  screenSize/2;
	
	double dx = center.x - x;
	double dy = center.y - y;
	double rad = atan2(dy, dx);
	double degree = (rad*180)/M_PI;

	body->setRotation(-degree-90);
}
void Player::processEyeline(
	float x,float y){

	Node *contactObject = nullptr;
	Vec2 contactPoint = Vec2(x,y);
	getPhysicsBody()->getWorld()->rayCast(
		[&](PhysicsWorld &world, const PhysicsRayCastInfo& info, void* data){
			if(info.shape == getPhysicsBody()->getShape(0))
				return true;

			contactPoint = info.contact;
			contactObject = info.shape->getBody()->getNode();
			return false;
		},
		getPosition(), Vec2(x,y),
		nullptr);

	lay->clear();
	lay->drawSegment(
		Vec2(0,0), contactPoint - getPosition(), 3, Color4F(1,0,0,1));

	auto pool = EnemyPool::getInstance();
	if(contactObject){
		pool->focus((Enemy*)contactObject);
	}
	else{
		pool->focus(nullptr);
	}
}
void Player::processMove(
	EventKeyboard::KeyCode keycode){

	Vec2 moveBy(0,0);

	switch(keycode){
	/* UP */
	case EventKeyboard::KeyCode::KEY_W:
		moveBy.set(0, speed); break;
	/* RIGHT */
	case EventKeyboard::KeyCode::KEY_D:
		moveBy.set(speed, 0); break;
	/* LEFT */
	case EventKeyboard::KeyCode::KEY_A:
		moveBy.set(-speed, 0); break;
	/* DOWN */
	case EventKeyboard::KeyCode::KEY_S:
		moveBy.set(0, -speed); break;
	}

	float frameRate =
		Director::getInstance()->getFrameRate();
	runAction(
		MoveBy::create(1.0/frameRate, moveBy))
		->setTag(actionMove);
}
void Player::processAttack(
	int btn, float x,float y){

	if(btn == MOUSE_BUTTON_LEFT){

	}
	else if(btn == MOUSE_BUTTON_RIGHT){
		auto bullet = Bullet::create();
		auto pos = getPosition();
		Vec2 norm = Vec2(x-pos.x, y-pos.y);
		
		norm.normalize();

		bullet->fire(norm.x,norm.y, 50000);
		bullet->setPosition(getPosition());

		getParent()->addChild(bullet);
	}
}

void Player::onKeyboardDown(
	EventKeyboard::KeyCode keycode){
}
void Player::onKeyboardUp(
	EventKeyboard::KeyCode keycode){
}
void Player::onKeyboardPressed(
	EventKeyboard::KeyCode keycode){

	processEyeline(cursor.x, cursor.y);
	processMove(keycode);
}

void Player::onMouseMove(
	int btn, float x,float y){

	processEyeline(x,y);
	processRotation(x,y);

	cursor.set(x,y);
}
void Player::onMouseDown(
	int btn, float x,float y){

	processAttack(btn, x,y);
}
void Player::onMouseUp(
	int btn, float x,float y){
}
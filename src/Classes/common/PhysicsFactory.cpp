#include "PhysicsFactory.h"

#include "config.h"
#include "objects/Unit.h"

using namespace std;
using namespace cocos2d;

static PhysicsFactory *instance = nullptr;

PhysicsFactory *PhysicsFactory::create(){
	instance = new PhysicsFactory();

	return instance;
}
PhysicsFactory *PhysicsFactory::getInstance(){
	return instance;
}

PhysicsBody *PhysicsFactory::make(
	const string &name){

	PhysicsBody *body;

	string type;
	_CONFIG_STR(name + "::shape", type);

	if(type == "circle"){
		float radius;
		_CONFIG_FLT(name + "::shape_size", radius);
		body = (PhysicsBody*)PhysicsBody::createCircle(radius);
	}
	else if(type == "box"){
		float width, height;
		_CONFIG_FLT(name + "::shape_size_width", width);
		_CONFIG_FLT(name + "::shape_size_height", height);
		body = (PhysicsBody*)PhysicsBody::createBox(
			Size(width, height));
	}

	int rotationEnabled;
	_CONFIG_INT(name + "::rotation_enabled", rotationEnabled);
	body->setRotationEnable(rotationEnabled);

	float angularDamping, linearDamping;
	_CONFIG_FLT(name + "::angular_damping", angularDamping);
	body->setAngularDamping(angularDamping);
	_CONFIG_FLT(name + "::linear_damping", linearDamping);
	body->setLinearDamping(linearDamping);

	float density;
	body->setRotationEnable(linearDamping);
	_CONFIG_FLT(name + "::density", density);
	body->getShape(0)->setDensity(density);

	string category;
	_CONFIG_STR(name + "::category", category);
	if(category == "bullet")
		body->setCategoryBitmask(Unit::channelBullet);
	else if(category == "enemy")
		body->setCategoryBitmask(Unit::channelEnemy);
	else if(category == "player")
		body->setCategoryBitmask(Unit::channelPlayer);

	int bitmask = 0;
	string collideWith;
	_CONFIG_STR(name + "::collide_with", collideWith);
	if(collideWith.find("bullet") != string::npos)
		bitmask |= Unit::channelBullet;
	if(collideWith.find("enemy") != string::npos)
		bitmask |= Unit::channelEnemy;
	if(collideWith.find("player") != string::npos)
		bitmask |= Unit::channelPlayer;
	body->setCollisionBitmask(bitmask);

	return body;
}
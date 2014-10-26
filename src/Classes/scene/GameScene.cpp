#include "GameScene.h"
#include "AppMacros.h"

#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EnemyPool.h"

using namespace cocos2d;

Scene* GameScene::scene(){
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();

	world->setDebugDrawMask(
		PhysicsWorld::DEBUGDRAW_NONE);
	world->setGravity(Vec2(0,0));

    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    if (!Layer::init())
        return false;
    
	
	auto pool = EnemyPool::create();
	auto spawner = EnemySpawner::create();

	addChild(pool);
	addChild(spawner);

	spawner->spawn();
	
	player = Player::create();

	player->setPosition(
		Vec2(100,100));
	addChild(player);

    return true;
}
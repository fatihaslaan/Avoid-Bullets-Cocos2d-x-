#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "Bullet.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Game);

private:
	Bullet bullet;

	bool holdButton = false; //Is button held down
	float animationTime = 0.5f; //Animation duration
	float thrust = 3; //Value of force that moves our character
	float bulletSpawnRate = 1; //Bullet spawn frequency (Lower for more bullets in a second)

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* character; //Our character
	cocos2d::ActionInterval* move; //Our move action
	cocos2d::PhysicsWorld* sceneWorld;

	cocos2d::Vec2 moveTowards; //Current move direction
	cocos2d::Vec2 moveUp = cocos2d::Vec2(0, thrust);
	cocos2d::Vec2 moveDown = cocos2d::Vec2(0, -thrust);
	cocos2d::Vec2 moveRight = cocos2d::Vec2(thrust, 0);
	cocos2d::Vec2 moveLeft = cocos2d::Vec2(-thrust, 0);

	bool onContactBegin(cocos2d::PhysicsContact& contact); //Collision happened
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
	void update(float);
	void MoveCharacter(cocos2d::Vec2);
	void SpawnBullet(float dt);
};

#endif

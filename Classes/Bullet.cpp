#include "Bullet.h"
#include "Definitions.h"

USING_NS_CC;

Bullet::Bullet()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Bullet::SpawnBullet(cocos2d::Layer* layer)
{
	bullet = Sprite::create("HelloWorld.png");
	bullet->setScale(0.05f);
	auto bulletBody = PhysicsBody::createBox(bullet->getContentSize());

	auto randomStartingFace = CCRANDOM_0_1();
	auto randomFinalFace = CCRANDOM_0_1();

	Vec2 a, b; //One will be startingPosition and the other one will be finalPosition, related to randomSide value

	if (randomStartingFace < 0.5f) //First position is somewhere in the top of the screen
	{
		a = Vec2(cocos2d::RandomHelper::random_real(origin.x, origin.x + visibleSize.width), origin.y + visibleSize.height + 10);
	}
	else //First position is somewhere in the right of the screen
	{
		a = Vec2(origin.x + visibleSize.width + 10, cocos2d::RandomHelper::random_real(origin.y, origin.y + visibleSize.height));
	}
	if (randomFinalFace < 0.5f) //Second position is somewhere in the down of the screen
	{
		b = Vec2(cocos2d::RandomHelper::random_real(origin.x, origin.x + visibleSize.width), origin.y - 10);
	}
	else //Second position is somewhere in the left of the screen
	{
		b = Vec2(origin.x - 10, cocos2d::RandomHelper::random_real(origin.y, origin.y + visibleSize.height));
	}

	auto randomSide = CCRANDOM_0_1();
	if (randomSide < 0.5f) //Change bullet starting position side and make the bullets come from everywhere
	{
		startingPosition = a;
		finalPosition = b;
	}
	else
	{
		startingPosition = b;
		finalPosition = a;
	}
	
	bulletBody->setDynamic(false);
	bulletBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bulletBody->setContactTestBitmask(true);

	bullet->setPhysicsBody(bulletBody);
	bullet->setPosition(startingPosition); //Set position of our bullet to startingPosition

	layer->addChild(bullet);

	auto fireBulletAction = MoveTo::create(bulletSpeed, finalPosition);

	bullet->runAction(fireBulletAction); //Fire bullet to finalPosition
}
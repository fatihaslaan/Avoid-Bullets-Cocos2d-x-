#ifndef __Bullet_SCENE_H__
#define __Bullet_SCENE_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Scene
{
public:

	Bullet();
	void SpawnBullet(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Vec2 startingPosition; //Bullet's starting position
	cocos2d::Vec2 finalPosition; //Bullet's final position

	float bulletSpeed = 2; //Bullet speed (Higher it is, slower it gets)

	cocos2d::Sprite* bullet; //Bullet sprite
};

#endif

#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOver);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	void GoToGameScene(); //Retry
};

#endif

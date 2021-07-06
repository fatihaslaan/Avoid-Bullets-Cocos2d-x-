#include "GameOver.h"
#include "Game.h"

USING_NS_CC;
using namespace ui;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto gameOverText = Label::createWithSystemFont("Game Over!", "Arial", 48); //Game over text with scale animation
	gameOverText->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/1.5f));
	auto scaleAction = ScaleTo::create(1, 1.5f);
	gameOverText->runAction(scaleAction);
	this->addChild(gameOverText);

	auto retryText = Label::createWithSystemFont("Click Button To Lose Again!", "Arial", 36); //Retry text
	retryText->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5f- gameOverText->getContentSize().height));
	this->addChild(retryText);

	//Buttons
	{
		auto retry = Button::create("CloseNormal.png"); //Retry button
		retry->setPosition(Vec2(origin.x + visibleSize.width/2, (origin.y + (visibleSize.height/1.5f)- gameOverText->getContentSize().height) - retryText->getContentSize().height));
		retry->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				GoToGameScene();
				break;
			default:
				break;
			}
			});
		this->addChild(retry);
	}
	return true;
}

void GameOver::GoToGameScene() //Change scene to play again
{
	auto scene = Game::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}
#include "Game.h"
#include "Definitions.h"
#include "GameOver.h"

USING_NS_CC;
using namespace ui;

Scene* Game::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //Red borderline around physic bodies
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = Game::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setDynamic(false); //Effect by collisions and gravity?
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK); //To check when collision happens
	edgeBody->setContactTestBitmask(true); //Collide with everything

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	character = Sprite::create("HelloWorld.png");
	character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	character->setScale(0.2f);

	auto characterBody = PhysicsBody::createBox(character->getContentSize());
	characterBody->setDynamic(true);
	characterBody->setCollisionBitmask(CHARACTER_COLLISION_BITMASK);
	characterBody->setContactTestBitmask(true);
	character->setPhysicsBody(characterBody);

	this->addChild(character, 0);

	//Buttons
	{
		auto left = Button::create("CloseNormal.png");
		left->setPosition(Vec2(origin.x + left->getContentSize().width, origin.y + left->getContentSize().height * 2));
		left->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				holdButton = true; //Button held down
				moveTowards = moveLeft; //Character's direction
				break;
			case ui::Widget::TouchEventType::ENDED:
				holdButton = false; //Button released
				break;
			default:
				break;
			}
			});
		this->addChild(left);

		auto right = Button::create("CloseNormal.png");
		right->setPosition(Vec2((origin.x + right->getContentSize().width + left->getContentSize().width * 2), origin.y + right->getContentSize().height * 2));
		right->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				holdButton = true;
				moveTowards = moveRight;
				break;
			case ui::Widget::TouchEventType::ENDED:
				holdButton = false;
				break;
			default:
				break;
			}
			});
		this->addChild(right);

		auto up = Button::create("CloseNormal.png");
		up->setPosition(Vec2((origin.x + right->getContentSize().width + left->getContentSize().width), origin.y + right->getContentSize().height * 3));
		up->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				holdButton = true;
				moveTowards = moveUp;
				break;
			case ui::Widget::TouchEventType::ENDED:
				holdButton = false;
				break;
			default:
				break;
			}
			});
		this->addChild(up);

		auto down = Button::create("CloseNormal.png");
		down->setPosition(Vec2((origin.x + right->getContentSize().width + left->getContentSize().width), origin.y + right->getContentSize().height));
		down->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				holdButton = true;
				moveTowards = moveDown;
				break;
			case ui::Widget::TouchEventType::ENDED:
				holdButton = false;
				break;
			default:
				break;
			}
			});
		this->addChild(down);
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this); //Listens collisions
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(CC_SCHEDULE_SELECTOR(Game::SpawnBullet), bulletSpawnRate); //Spawn bullets
	this->scheduleUpdate();

	return true;
}

void Game::update(float updateCounter)
{
	if (holdButton)
	{
		MoveCharacter(moveTowards); //Move character if any button held down
	}
}

void Game::MoveCharacter(Vec2 direction) //Move our character with given direction
{
	move = MoveBy::create(animationTime, direction);
	character->runAction(move);
}

void Game::SpawnBullet(float dt)
{
	bullet.SpawnBullet(this);
}

bool Game::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody(); //One of collision contacts
	PhysicsBody* b = contact.getShapeB()->getBody(); //Other

	//We only check collision between Character and Obstacle and not between Obstacle and Obstacle with Bitmasks
	if ((CHARACTER_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (CHARACTER_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		log("Collision!");
		auto scene = GameOver::createScene(); //Change scene to GameOver scene

		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}

	return true;
}

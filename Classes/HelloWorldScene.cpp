#include <string>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TestScene3.h"
#include "MainScreen.h"

USING_NS_CC;

Label *txt_cyan = Label::create();
Label *txt_magenta = Label::create();
Label *txt_yellow = Label::create();

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }


	layer1 = Layer::create();
	this->addChild(layer1);
	
	layer2 = Layer::create();
	this->addChild(layer2);

	winSize = Director::getInstance()->getWinSize();
	
	this->createBackground();
	this->createMan();
	this->createArrowButtons();


	MenuItemFont *menuitem_exit = MenuItemFont::create("STOP GAME", CC_CALLBACK_1(HelloWorld::stopGame, this));
	menuitem_exit->setColor(Color3B::BLACK);

	Menu *menu = Menu::create( menuitem_exit , nullptr);

	menu->setPosition(Vec2(240, 360));
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}




void HelloWorld::stopGame(Ref * sender)
{
	Scene *scene = MainScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::createMan()
{
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/grossini.plist");

	Vector<SpriteFrame*> animationFrames;

	char str[100] = { 0 };
	for (int i = 5; i < 11; ++i)
	{
		sprintf(str, "grossini_dance_%02d.png", i);
		SpriteFrame *frame = cache->getSpriteFrameByName(str);
		animationFrames.pushBack(frame);
	}

	Man = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	Man->setPosition(Vec2(240, 160));
	layer1->addChild(Man);

	Animation *animation = Animation::createWithSpriteFrames(animationFrames, 0.4f);
	Animate *animate = Animate::create(animation);
	RepeatForever *rep = RepeatForever::create(animate);
	Man->runAction(rep);
}

void HelloWorld::createBackground()
{
	Sprite *background1 = Sprite::create("sea.jpg");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	layer1->addChild(background1);
}

void HelloWorld::createArrowButtons()
{
	leftSprite = Sprite::create("b1.png");
	leftSprite->setPosition(Vec2(180, 30));
	layer2->addChild(leftSprite, 2);

	leftPressedSprite = Sprite::create("b2.png");
	leftPressedSprite->setPosition(leftSprite->getPosition());
	layer2->addChild(leftPressedSprite, 1);

	rightSprite = Sprite::create("f1.png");
	rightSprite->setPosition(Vec2(300, 30));
	layer2->addChild(rightSprite, 2);

	rightPressedSprite = Sprite::create("f2.png");
	rightPressedSprite->setPosition(rightSprite->getPosition());

	layer2->addChild(rightPressedSprite, 1);
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit()
{
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	isLeftPressed = false;
	isRightPressed = false;

	if (this->isTouchInside(leftSprite, touch))
	{
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}
	else if (this->isTouchInside(rightSprite, touch))
	{
		rightSprite->setVisible(false);
		isRightPressed = true;
	}
	if (isLeftPressed || isRightPressed)
	{
		this->startMovingBackground();
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	if (isLeftPressed && !this->isTouchInside(leftSprite, touch))
	{
		leftSprite->setVisible(true);
		this->stopMovingBackground();
	}
	else if (isRightPressed && !this->isTouchInside(rightSprite, touch))
	{
		rightSprite->setVisible(true);
		this->startMovingBackground();
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if (isLeftPressed || isRightPressed)
	{
		this->stopMovingBackground();
	}

	if (isLeftPressed)
	{
		leftSprite->setVisible(true);
	}
	if (isRightPressed)
	{
		rightSprite->setVisible(true);
	}
}

bool HelloWorld::isTouchInside(Sprite* sprite, Touch* touch)
{
	Vec2 touchPoint = touch->getLocation();
	bool bTouch = sprite->getBoundingBox().containsPoint(touchPoint);
	return bTouch;
}

void HelloWorld::startMovingBackground()
{
	if(isLeftPressed&&isRightPressed)
	{
		return;
	}

	log("start moving");
	this->schedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::stopMovingBackground()
{
	log("stop moving!");
	this->unschedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::moveBackground(float f)
{
	int moveStep = 3;

	if (isLeftPressed)
	{
		moveStep = -3;
		Man->setFlippedX(false);
	}
	else
	{
		moveStep = 3;
		Man->setFlippedX(true);
	}

	Vec2 newPosition = Vec2(Man->getPosition().x + moveStep, Man->getPosition().y);

	if (newPosition.x < 0)
	{
		newPosition.x = 0;
	}
	else if (newPosition.x > 1280)
	{
		newPosition.x = 1280;
	}

	Man->setPosition(newPosition);
	layer1->runAction(Follow::create(Man, Rect(0, 0, 1028, 720)));
}


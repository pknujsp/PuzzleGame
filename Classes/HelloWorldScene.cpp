#include <string>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
	winSize = Director::getInstance()->getWinSize();
	
	this->createBackground();
	this->createMan();
	this->createArrowButtons();


	return true;
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
	this->addChild(Man);

	Animation *animation = Animation::createWithSpriteFrames(animationFrames, 0.4f);
	Animate *animate = Animate::create(animation);
	RepeatForever *rep = RepeatForever::create(animate);
	Man->runAction(rep);
}

void HelloWorld::createBackground()
{
	Layer *voidNode = Layer::create();


	Sprite *background1 = Sprite::create("sea.jpg");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	voidNode->addChild(background1);
	this->addChild(voidNode);
}

void HelloWorld::createArrowButtons()
{
	leftSprite = Sprite::create("b1.png");
	leftSprite->setPosition(Vec2(180, 30));
	this->addChild(leftSprite, 2);

	leftPressedSprite = Sprite::create("b2.png");
	leftPressedSprite->setPosition(leftSprite->getPosition());
	this->addChild(leftPressedSprite, 1);

	rightSprite = Sprite::create("f1.png");
	rightSprite->setPosition(Vec2(300, 30));
	this->addChild(rightSprite, 2);

	rightPressedSprite = Sprite::create("f2.png");
	rightPressedSprite->setPosition(rightSprite->getPosition());

	this->addChild(rightPressedSprite, 1);
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
	log("start moving!");
}

void HelloWorld::stopMovingBackground()
{
	log("stop moving!");
}

void HelloWorld::moveBackground(float f)
{
	log("moving background!");
}
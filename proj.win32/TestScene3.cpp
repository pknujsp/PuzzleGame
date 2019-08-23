#include "TestScene3.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

Scene* TestScene3::creatScene()
{
	return TestScene3::create();
}

bool TestScene3::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Layer *background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background);

	MenuItemFont *item1 = MenuItemFont::create
	("Close Scene 3", CC_CALLBACK_1(TestScene3::doClose, this));
	item1->setColor(Color3B(0, 0, 0));

	Menu *menu = Menu::create(item1, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(240, 360));

	this->addChild(menu);
}

void TestScene3::doClose(Ref * sender)
{
	Scene *scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
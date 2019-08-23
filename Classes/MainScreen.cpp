#include <string>
#include "MainScreen.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScreen::createScene()
{
	return MainScreen::create();
}


static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScreen::init()
{
	if (!Scene::init())
	{
		return false;
	}
	Layer *background = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background);

	MenuItemFont *menuitem1 = MenuItemFont::create
	("close Scene 2", CC_CALLBACK_1(MainScreen::doClose,this));
	menuitem1->setColor(Color3B::BLACK);

	Menu *menu = Menu::create(menuitem1, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(240, 360));
	this->addChild(menu);

	return true;
}

void MainScreen::doClose(Ref * sender)
{
	Director::getInstance()->popScene();
}
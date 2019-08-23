#include <string>
#include "MainScreen.h"
#include "HelloWorldScene.h"
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

	MenuItemFont *menuitem_play = MenuItemFont::create("PLAY", CC_CALLBACK_1(MainScreen::playGame, this));
	menuitem_play->setColor(Color3B::BLACK);

	MenuItemFont *menuitem_exit = MenuItemFont::create("HISTORY", CC_CALLBACK_1(MainScreen::exitGame, this));
	menuitem_exit->setColor(Color3B::BLACK);

	MenuItemFont *menuitem_history = MenuItemFont::create("EXIT", CC_CALLBACK_1(MainScreen::showHistory, this));
	menuitem_history->setColor(Color3B::BLACK);

	Menu *menu = Menu::create(menuitem_play, menuitem_exit, menuitem_history,nullptr);

	menu->setPosition(Vec2(640, 360));
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}

void MainScreen::doReplaceScene(Ref* sender)
{
	Scene *scene = MainScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainScreen::playGame(Ref * sender)
{
	Scene *scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainScreen::exitGame(Ref * sender)
{
	Scene *scene = MainScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainScreen::showHistory(Ref * sender)
{
	Scene *scene = MainScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}


void MainScreen::doClose(Ref * sender)
{
	Director::getInstance()->popScene();
}
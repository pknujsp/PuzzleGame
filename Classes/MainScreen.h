#ifndef __MAINSCREEN_H__
#define __MAINSCREEN_H__

#include "cocos2d.h"

class MainScreen : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScreen);

	void doClose(Ref* sender);
};

#endif //__MAINSCREEN_H__
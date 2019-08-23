#ifndef __SCENETRANS__TESTSCENE3__
#define __SCENETRANS__TESTSCENE3__

#include "cocos2d.h"

class TestScene3 : public cocos2d::Scene
{
public:
	static cocos2d::Scene *creatScene();

	virtual bool init();

	CREATE_FUNC(TestScene3);

	void doClose(Ref* sender);
};

#endif // !__SCENETRANS__TESTSCENE3__

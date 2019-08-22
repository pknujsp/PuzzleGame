#include "Monster.h"

USING_NS_CC;

Monster* Monster::create(const std::string& filename)
{
	Monster *sprite = new(std::nothrow)Monster();

	if (sprite&&sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Monster::setPriority(int fixedPriority)
{
	_fixedPriority = fixedPriority;
}

void Monster::setPriorityWithThis(bool useNodePriority)
{
	_useNodePriority = useNodePriority;
}

void Monster::onEnter()
{
	Sprite::onEnter();

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		log("touch began...");

		Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			this->setColor(Color3B::RED);
			return true;
		}
		else
		{
			return false;
		}
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{

	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		this->setColor(Color3B::WHITE);
	};

	if (_useNodePriority)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else
	{
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
	}
	_listener = listener;
}

void Monster::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Sprite::onExit();
}
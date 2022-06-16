
#include "GameFigure.h"
#include "GameField.h"
#include <random>
USING_NS_CC;

GameFigure::~GameFigure()
{

}

bool GameFigure::init()
{
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(0, 2); // distribute results between 1 and 6 inclusive.

	sprite = Sprite::create();
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	SpriteFrame* frame; cache->getSpriteFrameByName("./Uvash_CMO");

	switch (dist(gen))
	{
		case(0): {frame = cache->getSpriteFrameByName("./Uvash_CMO"); break; }
		case(1): {frame = cache->getSpriteFrameByName("./Uvash_CE"); break; }
		case(2): {frame = cache->getSpriteFrameByName("./Uvash_HoS"); break; }
	}

	if (!frame)
		return false;

	sprite->setSpriteFrame(frame);
	addChild(sprite);
	setTouchEnabled(true);
	setFocusEnabled(false);
	sprite->setAnchorPoint({0.0, 0.0 });

	addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) 
	{
		/*SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		frame = cache->getSpriteFrameByName("./Uvash_CE");
		sprite->setSpriteFrame(frame);
		*/
		if(type == ui::Widget::TouchEventType::BEGAN)
			master->clickCallback(this);
	});
	return true;
}


void GameFigure::initRenderer()
{
	sprite = Sprite::create();
	addProtectedChild(sprite);
}

Node* GameFigure::getVirtualRenderer()
{
	return sprite;
}

void GameFigure::copySpecialProperties(Widget* model)
{
	Widget::copySpecialProperties(model);
}


void GameFigure::setPosition(const Vec2& pos)
{
	Widget::setPosition(pos);
	//sprite->setPosition(pos);
}


const Size& GameFigure::getContentSize() const
{
	return sprite->getContentSize();
}

const point2i& GameFigure::getCoordinats()
{
	return coordinats;
}

void GameFigure::setCoordinats(const point2i& target)
{
	coordinats = target;
}
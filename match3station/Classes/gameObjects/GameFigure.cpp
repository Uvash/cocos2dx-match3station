
#include "GameFigure.h"
#include "GameMode.h"
#include <random>
USING_NS_CC;

GameFigure::GameFigure(GameMode& mode) : gameMode{mode}
{

}

GameFigure::~GameFigure()
{

}

bool GameFigure::init()
{
	sprite = Sprite::create();
	SpriteFrame* frame;

	addChild(sprite);

	setTouchEnabled(true);
	setFocusEnabled(false);
	sprite->setAnchorPoint({0.0, 0.0 });

	addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) 
	{
		if(type == ui::Widget::TouchEventType::BEGAN)
			gameMode.clickCallback(this);
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


void GameFigure::setScreenPosition(const Vec2& pos)
{
	Widget::setPosition(pos);
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

void GameFigure::setFigureType(FigureType type)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	SpriteFrame* frame = nullptr;

	switch (type) 
	{	
		//case(FigureType::assistant) : { break; }
		case(FigureType::CMO):	{frame = cache->getSpriteFrameByName("./Uvash_CMO"); break; }
		case(FigureType::CE):	{frame = cache->getSpriteFrameByName("./Uvash_CE"); break; }
		case(FigureType::HOS):	{frame = cache->getSpriteFrameByName("./Uvash_HoS"); break; }
		default: {throw std::exception{"GameFigure: try to set unknown type"}; break; }
	}

	if(sprite != nullptr)
		sprite->setSpriteFrame(frame);
	gameType = type;
}

GameFigure* GameFigure::create(GameMode& mode)
{
	GameFigure* pRect = new(std::nothrow) GameFigure(mode);
	if (pRect && pRect->init())
	{
		pRect->autorelease();
		return pRect;
	}
	else
	{
		delete pRect;
		pRect = nullptr;
		return pRect;
	}
}
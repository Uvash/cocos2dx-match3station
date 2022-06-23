
#include "GameFigure.h"
#include "GameMode.h"
#include <random>
USING_NS_CC;

GameFigure::GameFigure(GameMode& mode) : gameMode{ mode }
{
	
}

GameFigure::~GameFigure()
{

}

bool GameFigure::init()
{
	if (!Widget::init()) {
		return false;
	}

	sprite = Sprite::create();
	SpriteFrame* frame;

	addChild(sprite);
	setTouchEnabled(true);
	setFocusEnabled(false);
	
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
		case(FigureType::CMO):	{frame = cache->getSpriteFrameByName("./Uvash_CMO"); break; }
		case(FigureType::CE):	{frame = cache->getSpriteFrameByName("./Uvash_CE"); break; }
		case(FigureType::HOS):	{frame = cache->getSpriteFrameByName("./Uvash_HoS"); break; }
		default: {throw std::exception{"GameFigure: try to set unknown type"}; break; }
	}

	if(sprite != nullptr)
		sprite->setSpriteFrame(frame);

	setContentSize(sprite->getContentSize());
	setAnchorPoint({ 0.5f, 0.5f });
	sprite->setAnchorPoint({ 0.0f, 0.0f });

	gameType = type;
}

void GameFigure::setFigureStatus(FigureStatus gStatus)
{
	switch (gStatus)
	{
		case(FigureStatus::normal): 
		{
			setNormal();
			break; 
		}
		case(FigureStatus::choosen): 
		{
			setChoosen();
			break; 
		}
		default: {throw std::exception{ "GameFigure: try to set unknown status" }; break; }
	}

	gameStatus = gStatus;
}

FigureType GameFigure::getFigureType()
{
	return gameType;
}

FigureStatus GameFigure::getFigureStatus()
{
	return gameStatus;
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

void GameFigure::setChoosen()
{
	auto rotateBy = RotateBy::create(2.0f, 360.0f);
	runAction(RepeatForever::create(rotateBy));
}

void GameFigure::setNormal()
{
	stopAllActions();
	setRotation(0);
}
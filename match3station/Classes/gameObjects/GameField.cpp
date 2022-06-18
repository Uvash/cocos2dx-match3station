#include "GameField.h"
#include "GameFigure.h"
#include <functional>

USING_NS_CC;

GameField::~GameField()
{
	content.clear();
}



bool GameField::init()
{
	fillField();

	return true;
}

cocos2d::Vec2 GameField::getScreenPositionFrom2i(point2i target)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size offsetPerNode{ visibleSize.width / (size.w + 1), visibleSize.height / (size.h + 1) };
	return { offsetPerNode.width * (target.w + 1) - spriteSize / 2, offsetPerNode.height * (target.h + 1) - spriteSize / 2 };
}

bool GameField::checkScopeField(point2i target)
{
	if (target.x >= size.x && target.x < 0 && target.y >= size.y && target.y < 0)
		return false;
	return true;
}


int GameField::getFigureAddressFromFieldCoordinats(point2i target)
{
	return target.h * size.w + target.w;
}
point2i GameField::getFieldCoordinatsFromFigureAddress(int address)
{
	return { address % size.h, address / size.w };
}

GameFigure* GameField::getFigureFromField(point2i target)
{
	if (!checkScopeField(target))
		return nullptr;

	size_t addresInVector = getFigureAddressFromFieldCoordinats(target);
	return content[addresInVector];
}

void GameField::clickCallback(GameFigure* target)
{
	if (target == nullptr)
	{
		throw std::runtime_error("GameField: Try to call target nullptr");
		return;
	}

	if (clicked == nullptr)
	{
		clicked = target;
		return;
	}

	if (clicked == target)
	{
		clicked = nullptr;
		return;
	}

	swapFigure(content.begin() + getFigureAddressFromFieldCoordinats(clicked->getCoordinats()), content.begin() + getFigureAddressFromFieldCoordinats(target->getCoordinats()));
	clicked = nullptr;
}

void GameField::swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt)
{
	point2i fieldPositionForFirst = (*firstIt)->getCoordinats();
	point2i fieldPositionForSecond = (*secondIt)->getCoordinats();

	cocos2d::Vec2 screenPositionForFirst = getScreenPositionFrom2i(fieldPositionForFirst);
	cocos2d::Vec2 screenPositionForSecond = getScreenPositionFrom2i(fieldPositionForSecond);

	std::iter_swap(firstIt, secondIt); //ѕомен€ли указатели в векторе местами

	(*firstIt)->setCoordinats(fieldPositionForFirst);
	(*firstIt)->setScreenPosition(screenPositionForFirst);

	(*secondIt)->setCoordinats(fieldPositionForSecond);
	(*secondIt)->setScreenPosition(screenPositionForSecond);
}

void GameField::fillField()
{
	SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("uvash.plist");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size offsetPerNode{ visibleSize.width / (size.w + 1), visibleSize.height / (size.h + 1) };

	content.resize(size.w * size.h, nullptr);
		
	int i = 0;
	std::for_each(content.begin(), content.end(), [&i, this](GameFigure* &pFigure)
	{
			pFigure = GameFigure::create(*this);
			auto coords = getFieldCoordinatsFromFigureAddress(i);
			pFigure->setScreenPosition(getScreenPositionFrom2i(coords));
			pFigure->setCoordinats(coords);
			this->addChild(pFigure);
			i++;
	});
}

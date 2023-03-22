#include "GameField.h"
#include "GameFigure.h"
#include "GameConfig.h"
#include <algorithm>
#include <functional>

USING_NS_CC;

GameField::GameField() : gameConfig{ gameConfig.getInstance() }
{
	screenSize = Director::getInstance()->getWinSize();
	screenSize.width = gameConfig.sizeGameField.width * screenSize.width + gameConfig.offsetForGameField.width * screenSize.width;
	screenSize.height = gameConfig.sizeGameField.height * screenSize.height + gameConfig.offsetForGameField.height * screenSize.height;


	cocos2d::Size offsetPerNode{ screenSize.width / (size.w + 1), screenSize.height / (size.h + 1) };
	
	
	/// TODO брать размер спрайтов из спрайтов а не магии
	figureScale = std::min(offsetPerNode.width / 64.0f, offsetPerNode.height / 64.0f);
}
GameField::~GameField()
{
	content.clear();
}



bool GameField::init()
{
	allocField();
	return true;
}


GameFigure* GameField::getFigureFromField(point2i target)
{
	if (!checkScopeField(target))
		return nullptr;

	size_t addresInVector = getFigureAddressFromFieldCoordinats(target);
	return content[addresInVector];
}

void GameField::replaceFigure(point2i position)
{
	size_t addres = getFigureAddressFromFieldCoordinats(position);

	if (!checkScopeField(addres))
		return;

	point2i fieldPosition = getFieldCoordinatsFromFigureAddress(addres);
	auto visibleSize = Director::getInstance()->getWinSize();

	cocos2d::Vec2 screenPosition = getScreenPositionFrom2i(fieldPosition);
	cocos2d::Vec2 spacePosition = { screenPosition.x, screenPosition.y + visibleSize.height };

	content[addres]->setScreenPosition(spacePosition);
	content[addres]->moveToScreenPosition(screenPosition);
}

void GameField::swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt)
{
	if (firstIt == secondIt)
		return;

	point2i fieldPositionForFirst = (*firstIt)->getCoordinats();
	point2i fieldPositionForSecond = (*secondIt)->getCoordinats();

	cocos2d::Vec2 screenPositionForFirst = getScreenPositionFrom2i(fieldPositionForFirst);
	cocos2d::Vec2 screenPositionForSecond = getScreenPositionFrom2i(fieldPositionForSecond);

	std::iter_swap(firstIt, secondIt); //Поменяли указатели в векторе местами

	(*firstIt)->setCoordinats(fieldPositionForFirst);

	(*secondIt)->setCoordinats(fieldPositionForSecond);

}

void GameField::swapFigure(point2i first, point2i second)
{
	auto firstIt = content.begin() + getFigureAddressFromFieldCoordinats(first);
	auto secondIt = content.begin() + getFigureAddressFromFieldCoordinats(second);
	swapFigure(firstIt, secondIt);
}

void GameField::moveToHomeOnScreen(point2i position)
{
	if (!checkScopeField(position))
		return;

	auto positionIt = content.begin() + getFigureAddressFromFieldCoordinats(position);
	(*positionIt)->moveToScreenPosition(getScreenPositionFrom2i(position));

}

bool GameField::moveIterator(std::vector<GameFigure*>::iterator& iter, size_t offset)
{
	if (offset == 0)
		return true;

	if(std::distance(iter, content.end()) <= offset)
		return false;

	iter += offset; // для гурманом можно заменить на advance

	if(checkScopeField(iter))
		return true;
	return false;
}

bool GameField::findNextWithCurrentStatus(std::vector<GameFigure*>::iterator& iter, FigureStatus searchStatus, size_t offset)
{
	if (!checkScopeField(iter))
		return false;

	auto searchCandidate = iter;
	bool flag = true;
	while (flag)
	{
		auto figureStatu = (*searchCandidate)->getFigureStatus();
		if (figureStatu != searchStatus)
		{
			flag = moveIterator(searchCandidate, offset);
			continue;
		}

		iter = searchCandidate;
		return true;
	}
	return false;
}


void GameField::addFigure(GameFigure* pfigure, std::vector<GameFigure*>::iterator iterAddres)
{
	if (*iterAddres != nullptr)
		return;

	if (pfigure == nullptr)
		return;

	if(iterAddres >= content.end())
		return;

	*iterAddres = pfigure;

	size_t addres = std::distance(content.begin(), iterAddres);

	point2i fieldPosition = getFieldCoordinatsFromFigureAddress(addres);
	cocos2d::Vec2 screenPositionForFirst = getScreenPositionFrom2i(fieldPosition);

	(*iterAddres)->setScale(figureScale);
	(*iterAddres)->setCoordinats(fieldPosition);
	(*iterAddres)->setScreenPosition(screenPositionForFirst);
}

void GameField::allocField()
{
	content.resize(size.w * size.h, nullptr);
}


bool GameField::checkScopeField(point2i target)
{
	if (target.x != std::clamp(target.x, 0, size.x - 1))
		return false;
	if (target.y != std::clamp(target.y, 0, size.y - 1))
		return false;
	//Не уверен что будет работать быстрее покомпонентного сравнения, но так читаемее
	size_t adr = getFigureAddressFromFieldCoordinats(target);
	return checkScopeField(adr);
}

bool GameField::checkScopeField(size_t target)
{
	if (target != std::clamp(target, static_cast<size_t>(0), static_cast<size_t>(content.size() - 1)))
		return false;
	return true;
}

bool GameField::checkScopeField(std::vector<GameFigure*>::iterator target)
{
	if (target != std::clamp(target, content.begin(), content.end() - 1) )
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

FigureType GameField::getFiureType(point2i address, point2i offset)
{
	size_t addres = getFigureAddressFromFieldCoordinats(address + offset);
	if (checkScopeField(addres))
	{
		GameFigure* figure = content[addres];
		return figure->getFigureType();
	}

	return FigureType::maxFigure;
}

cocos2d::Vec2 GameField::getScreenPositionFrom2i(point2i target)
{
	cocos2d::Size offsetPerNode{ screenSize.width / (size.w + 1), screenSize.height / (size.h + 1) };
	return { offsetPerNode.width * (target.w + 1), offsetPerNode.height * (target.h + 1)};
}
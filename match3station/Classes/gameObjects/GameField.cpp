#include "GameField.h"
#include "GameFigure.h"
#include <algorithm>
#include <functional>

USING_NS_CC;

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

void GameField::clickCallback(GameFigure* target)
{

}

void GameField::swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt)
{
	if (firstIt == secondIt)
		return;

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

void GameField::swapFigure(point2i first, point2i second)
{
	auto firstIt = content.begin() + getFigureAddressFromFieldCoordinats(first);
	auto secondIt = content.begin() + getFigureAddressFromFieldCoordinats(second);
	swapFigure(firstIt, secondIt);
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

	(*iterAddres)->setCoordinats(fieldPosition);
	(*iterAddres)->setScreenPosition(screenPositionForFirst);
}

void GameField::allocField()
{
	content.resize(size.w * size.h, nullptr);
}


bool GameField::checkScopeField(point2i target)
{
	//Ќе уверен что будет работать быстрее покомпонентного сравнени€, но так читаемее
	size_t adr = getFigureAddressFromFieldCoordinats(target);
	return checkScopeField(adr);
}

bool GameField::checkScopeField(size_t target)
{
	if (target != std::clamp(target, static_cast<size_t>(0), static_cast<size_t>(content.size() - 1)))
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

cocos2d::Vec2 GameField::getScreenPositionFrom2i(point2i target)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size offsetPerNode{ visibleSize.width / (size.w + 1), visibleSize.height / (size.h + 1) };
	return { offsetPerNode.width * (target.w + 1), offsetPerNode.height * (target.h + 1)};
}
#include "GameField.h"
#include "GameFigure.h"

USING_NS_CC;

GameField::~GameField()
{
	content.clear();
}



bool GameField::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("uvash.plist");

	content.reserve(size.w * size.h);

	Size offsetPerNode{ visibleSize.width / (size.w + 1), visibleSize.height / (size.h + 1)};

	for (int height = 0; height < size.h; height++)
	{
		for (int width = 0; width < size.w; width++)
		{
			GameFigure* gameFigure = GameFigure::create();
			gameFigure->setPosition(getScreenPositionFrom2i({ width , height }));
			gameFigure->setCoordinats({ width , height });
			gameFigure->master = this;
			content.push_back(gameFigure);
			addChild(gameFigure);
		}
	}

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

void GameField::swapFigure(point2i firstFigutre, point2i secondFigure)
{
	if (!checkScopeField(firstFigutre))
		return;
	if (!checkScopeField(secondFigure))
		return;
	if(firstFigutre == secondFigure)
		return;

	int firstAddres = getFigureAddressFromField(firstFigutre);
	int secondAddres = getFigureAddressFromField(secondFigure);
	GameFigure* firstPointer = content[firstAddres];
	GameFigure* secondPointer = content[secondAddres];

	content[firstAddres] = secondPointer;
	content[secondAddres] = firstPointer;
	
	cocos2d::Vec2 pos1 = getScreenPositionFrom2i(firstFigutre);
	content[firstAddres]->setPosition(pos1);
	content[firstAddres]->setCoordinats(firstFigutre);

	cocos2d::Vec2 pos2 = getScreenPositionFrom2i(secondFigure);
	content[secondAddres]->setPosition(pos2);
	content[secondAddres]->setCoordinats(secondFigure);
}

int GameField::getFigureAddressFromField(point2i target)
{
	return target.h * size.w + target.w;
}
GameFigure* GameField::getFigureFromField(point2i target)
{
	if (!checkScopeField(target))
		return nullptr;

	size_t addresInVector = getFigureAddressFromField(target);
	return content[addresInVector];
}

void GameField::clickCallback(GameFigure* target)
{
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

	swapFigure(clicked->getCoordinats(), target->getCoordinats());
	clicked = nullptr;
}
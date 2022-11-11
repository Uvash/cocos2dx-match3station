#pragma once
#include "cocos2d.h"

class GameField;
class GameFigure;
class point2i;
enum class FigureType;
// Наследуемся от ноды, дабы соответствовать дао движка
class GameMode : public cocos2d::Node
{
public:
	void fillField();
	void clickCallback(GameFigure* figure);
	void checkCombination(point2i position);
	void updateCollum();
	void replaceDeleted();
	FigureType getRandomFigureType();
protected:
	GameField& gameField;
	GameFigure* clicked = nullptr;
	std::vector<point2i> getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset);

	int rowRequestToCombination = 3;
	int collumRequestToCombination = 3;

	std::vector <bool> collumFlags;
public:
	GameMode(GameField &gField);
	~GameMode() override;

	bool init() override;
	static GameMode* create(GameField& field);
};
#pragma once
#include "cocos2d.h"

class GameField;
class GameFigure;
// Наследуемся от ноды, дабы соответствовать дао движка
class GameMode : public cocos2d::Node
{
public:
	void fillField();
	void clickCallback(GameFigure* figure);

protected:
	GameField& gameField;
	GameFigure* clicked = nullptr;
public:
	GameMode(GameField &gField);
	~GameMode() override;

	bool init() override;
	static GameMode* create(GameField& field);
};
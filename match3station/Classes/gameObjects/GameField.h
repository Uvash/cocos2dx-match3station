#pragma once

#include "cocos2d.h"
#include <vector>
#include "HelpStructures.h"

class GameFigure;
class GameField: public cocos2d::Node
{
public:
    GameField() = default;
    ~GameField() override; 
    bool init() override;

    cocos2d::Vec2 getScreenPositionFrom2i(point2i target);
    bool checkScopeField(point2i target);
    inline int getFigureAddressFromFieldCoordinats(point2i target);
    inline point2i getFieldCoordinatsFromFigureAddress(int address);
    GameFigure* getFigureFromField(point2i target);
    void clickCallback(GameFigure* target);

protected:
    point2i size = {5, 5 };
    int spriteSize = 64;
    std::vector<GameFigure*> content;

    GameFigure* clicked = nullptr;

    void swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt);
    void fillField();
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);

};


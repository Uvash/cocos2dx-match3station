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
    void swapFigure(point2i firstFigutre, point2i secondFigure);
    inline int getFigureAddressFromField(point2i target);
    GameFigure* getFigureFromField(point2i target);
    void clickCallback(GameFigure* target);

protected:
    point2i size = {5, 5 };
    int spriteSize = 64;
    std::vector<GameFigure*> content;

    GameFigure* clicked = nullptr;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);
    
};
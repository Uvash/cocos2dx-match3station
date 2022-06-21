#pragma once

#include "cocos2d.h"
#include <vector>
#include "HelpStructures.h"

class GameFigure;
class GameMode;
class GameField: public cocos2d::Node
{
    friend GameMode;

public:
    void addFigure(GameFigure* pfigure, std::vector<GameFigure*>::iterator iterAddres);
    GameFigure* getFigureFromField(point2i target);
    void clickCallback(GameFigure* target);

protected:
    point2i size = {5, 5 };
    int spriteSize = 64;
    std::vector<GameFigure*> content;

    void swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt);
    void swapFigure(point2i first, point2i second);

    void allocField();
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);

    // ¬спомогательные функции дл€ преобразовани€ одномерных координат массива в двумерные игровые
    bool checkScopeField(point2i target);
    bool checkScopeField(size_t target);
    cocos2d::Vec2 getScreenPositionFrom2i(point2i target);
    //Ќе самое правильное решение возитьс€ с преобразованием size_t <-> int, но пока что оставим так
    inline int getFigureAddressFromFieldCoordinats(point2i target);
    inline point2i getFieldCoordinatsFromFigureAddress(int address);

public:
    GameField() = default;
    ~GameField() override;
    bool init() override;
};


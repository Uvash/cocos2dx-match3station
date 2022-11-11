#pragma once

#include "cocos2d.h"
#include <vector>
#include "HelpStructures.h"

class GameFigure;
class GameMode;
enum class FigureType;
enum class FigureStatus;
class GameField: public cocos2d::Node
{
    friend GameMode;

public:
    void addFigure(GameFigure* pfigure, std::vector<GameFigure*>::iterator iterAddres);
    GameFigure* getFigureFromField(point2i target);
    void replaceFigure(point2i position);
protected:
    point2i size = {5, 5 };
    int spriteSize = 64;
    std::vector<GameFigure*> content;

    void swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt);
    void swapFigure(point2i first, point2i second);

protected:
    bool moveIterator(std::vector<GameFigure*>::iterator& iter, size_t offset);
public:
    bool findNextWithCurrentStatus(std::vector<GameFigure*>::iterator& iter, FigureStatus searchStatus, size_t offset);

    void allocField();
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);

    // ¬спомогательные функции дл€ преобразовани€ одномерных координат массива в двумерные игровые
    bool checkScopeField(point2i target);
    bool checkScopeField(size_t target);
    bool checkScopeField(std::vector<GameFigure*>::iterator target);
    cocos2d::Vec2 getScreenPositionFrom2i(point2i target);
    //Ќе самое правильное решение возитьс€ с преобразованием size_t <-> int, но пока что оставим так
    inline int getFigureAddressFromFieldCoordinats(point2i target);
    inline point2i getFieldCoordinatsFromFigureAddress(int address);
    FigureType getFiureType(point2i address, point2i offset = {0, 0});
public:
    GameField();
    ~GameField() override;
    bool init() override;
};


/**
    \addtogroup match3station
    \brief игровой Интерфейс - класс описывающий интерфейс хранящий в себе полоски/счётчики и так далее. Берёт информацию у gameMode
*/
///@{

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

struct gameScore;

class GameUi : public cocos2d::Node
{
protected:
    
    cocos2d::ProgressTimer* hullConditionBar;
    cocos2d::ProgressTimer* crewHealthBar;
    cocos2d::ProgressTimer* orderBar;
    cocos2d::ui::Text* scoreText;
    
    cocos2d::ProgressTimer* prepareTimer(std::string spriteName);
    void fancySetTimerPercent(cocos2d::ProgressTimer* timer, float percent);
public:
    void updateGameUi(gameScore& score);
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameUi); ///< Макрос создающий необходимые для движка функции
    GameUi();
    ~GameUi();
};

///@}
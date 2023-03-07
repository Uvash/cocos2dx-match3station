/**
    \addtogroup match3station
    \brief Слой конца игры - класс хранящий кнопочки выскакивающие при проигрыше
*/
///@{

#pragma once

#include "cocos2d.h"

class EndGameUi : public cocos2d::Node
{

public:
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameUi); ///< Макрос создающий необходимые для движка функции

    EndGameUi();
    ~EndGameUi();

    void resetButtonCallback(Ref* pSender);
    void exitButtonCallback(Ref* pSender);
};

///@}
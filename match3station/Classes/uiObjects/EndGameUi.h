/**
    \addtogroup match3station
    \brief Слой конца игры - класс хранящий кнопочки выскакивающие при проигрыше
    Отображает на экране 2 кнопки - заново и выход. В первом варианте загружается новая HelloWorldScene 
*/
///@{

#pragma once

#include "cocos2d.h"

class EndGameUi : public cocos2d::Node
{

public:
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameUi); ///< Макрос создающий необходимые для движка функции

    /**
    \brief Конструктор класса. Создаёт внутри себя необходимые кнопки
    **/
    EndGameUi();

    /**
    \brief Деструктор класса.
    **/
    ~EndGameUi();

    /**
    \brief Каллбек. Вызывается если пользователь выбрал "новую игру"
    **/
    void resetButtonCallback(Ref* pSender);

    /**
    \brief Каллбек. Вызывается если пользователь выбрал "выйти из игры"
    **/
    void exitButtonCallback(Ref* pSender);
};

///@}
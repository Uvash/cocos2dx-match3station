/**
    \addtogroup match3station
    \brief игровой Интерфейс - класс описывающий интерфейс хранящий в себе полоски/счётчики и так далее. Получает информацию у gameMode
*/
///@{

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

struct gameScore;

class GameUi : public cocos2d::Node
{
protected:
    
    cocos2d::ProgressTimer* hullConditionBar;   ///< Бар отрисовывающая состояние корпуса
    cocos2d::ProgressTimer* crewHealthBar;  ///< Бар отрисовывающая состояние здоровья экипажа
    cocos2d::ProgressTimer* orderBar; ///< Бар отрисовывающая состояние порядка среди экипажа
    cocos2d::ui::Text* scoreText;   ///< Текст для вывода общего кол-ва очков
    
    /**
    \brief подгружает бар, с нужным спрайтом
    \param[in] spriteName название спрайта, хранящегося в кэше спрайтов
    \details Поскольку бары являются классам  cocos2d::ProgressTimer в методе фигурируют Timer-ы
     **/
    cocos2d::ProgressTimer* prepareTimer(std::string spriteName);

    /**
    \brief устанавливает новое значение бара, запуская его движение до нужного процента
    \param[in] timer указатель на бар
    \param[in] percent целевой процент
    \details Поскольку бары являются классам  cocos2d::ProgressTimer в методе фигурируют Timer-ы. Двжижение по умолчанию занимает 2 секунды
     **/
    void fancySetTimerPercent(cocos2d::ProgressTimer* timer, float percent);
public:
    /**
    \brief обновляет количество очков.
    \param[in] score ссылка на актуальное кол-во очков
     **/
    void updateGameUi(gameScore& score);
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameUi); ///< Макрос создающий необходимые для движка функции
    /**
    \brief Конструктор
     **/
    GameUi();

    /**
    \brief Деструктор
     **/
    ~GameUi();
};

///@}
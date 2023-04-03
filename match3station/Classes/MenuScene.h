/**
	\addtogroup match3station
	\brief Класс MenuScene. Создаёт сцену главного меню
*/
///@{
#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    /**
    \brief Каллбэк на закрытиые игры. 
    \param[in] pSender Указатель, на того кто вызвал
     **/
    void menuCloseCallback(cocos2d::Ref* pSender);

    /**
    \brief Каллбэк на запуск MainScene
    \param[in] pSender Указатель, на того кто вызвал
     **/
    void playCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);    ///< добавляем static create() для дерева сцены
protected:
    /**
    \brief Загружает спрайты в кэш
     **/
    void loadSprites();     ///< Вспомогательная функция для загрузки листа спрайтов
};
///@}
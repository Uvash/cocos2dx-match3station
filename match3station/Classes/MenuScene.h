/**
	\addtogroup match3station
	\brief Класс Сцена Меню. Создаёт сцену с меню
*/
///@{
#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void playCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);    ///< добавляем static create() для дерева сцены
protected:
    void loadSprites();     ///< Вспомогательная функция для загрузки листа спрайтов
};
///@}
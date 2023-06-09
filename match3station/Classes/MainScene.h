/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

 /**
     \addtogroup match3station
     \brief основной модуль, содержащей в себе описание игровой механики, отделёный от основного движка
 */
 ///@{
#pragma once

#include "cocos2d.h"

class GameField;
class GameMode;
class GameUi;

/**
    \brief класс MainScene. Основная игровая сцена
    К данной сцене мы будем привязывать виджеты. Сгенерирован кокосом при создании проекта.
*/
class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    /**
    \brief Каллбэк на закрытиые игры. Сгенерирован автоматически при созданнии проекта
    \param[in] pSender Указатель, на того кто вызвал
     **/
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);    ///< добавляем static create() для дерева сцены
protected:
    /**
    \brief Загружает спрайты в кэш
     **/
    void loadSprites();

    GameField* gameField;   ///< Элемент сцены - игровое поле для игры 3 в ряд
    GameMode* gameMode;     ///< Элемент сцены - режим игры для игры 3 в ряд
    GameUi* gameUi;         ///< Элемент сцены - отображает интерфейс игры
};
///@}

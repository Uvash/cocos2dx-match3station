#pragma once
/**
	\addtogroup match3station
	\brief Класс GameCongig хранит настройки необходимые для игры. Обхединяются в кучу, для того что бы в будущем читать из файла
*/
///@{
#pragma once
#include "cocos2d.h"

class GameConfig final
{
public:
    const cocos2d::Size offsetForGameField = {0, 0};    ///< Смещение по X Y для основного игрового поля от размеров экрана
    const cocos2d::Size sizeGameField = { 0.75, 1.0 };  ///< Размеры игрового поля относительно размеров экрана

    const cocos2d::Size offsetForScoresField = { 0.75, 0 }; ///< Смещение по X Y для поля очков от размеров экрана
    const cocos2d::Size sizeScoresField = { 0.25, 1.0 };    ///< Размеры поля очков относительно размеров экрана
public:
    static GameConfig& getInstance()
    {
        static GameConfig   instance; 
        return instance;
    }
private:
    GameConfig() {}
public:
    GameConfig(GameConfig const&) = delete;
    void operator=(GameConfig const&) = delete;
};

///@}
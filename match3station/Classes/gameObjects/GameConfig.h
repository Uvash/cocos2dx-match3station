#pragma once
/**
	\addtogroup match3station
	\brief Класс GameCongig хранит настройки необходимые для игры.
    
    \details Хранит разнообразные данные вместе. По идее должен хранить и читать их из файла, но пока залит бетоном из констант
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

    const float effectVolume = 1.0; ///< Громкость звука эффектов
public:
    /**
    * \brief Функция реализующая паттерн одиночка
    * \return Экземпляр класса GameConfig
    **/
    static GameConfig& getInstance()
    {
        static GameConfig   instance; 
        return instance;
    }
private:
    GameConfig() = default;
public:
    GameConfig(GameConfig const&) = delete;
    void operator=(GameConfig const&) = delete;
};

///@}
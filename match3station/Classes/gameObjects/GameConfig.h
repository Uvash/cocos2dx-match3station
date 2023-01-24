#pragma once
/**
	\addtogroup match3station
	\brief Класс GameCongig хранит настройки необходимые для игры. Обхединяются в кучу, для того что бы в будущем читать из файла
*/
///@{
#pragma once

class GameConfig final
{
public:
	const float gameFieldWidth	= 0.75;	///< Ширина занимаемая игровым полем в процентах от ширины экрана
	const float gameFieldHeight	= 1.0;	///< Высота занимаемая игровым полем в процентах от высоты экрана

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
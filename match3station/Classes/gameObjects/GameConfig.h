#pragma once
/**
	\addtogroup match3station
	\brief ����� GameCongig ������ ��������� ����������� ��� ����. ������������ � ����, ��� ���� ��� �� � ������� ������ �� �����
*/
///@{
#pragma once
#include "cocos2d.h"

class GameConfig final
{
public:
    const cocos2d::Size offsetForGameField = {0, 0};    ///< �������� �� X Y ��� ��������� �������� ���� �� �������� ������
    const cocos2d::Size sizeGameField = { 0.75, 1.0 };  ///< ������� �������� ���� ������������ �������� ������

    const cocos2d::Size offsetForScoresField = { 0.75, 0 }; ///< �������� �� X Y ��� ���� ����� �� �������� ������
    const cocos2d::Size sizeScoresField = { 0.25, 1.0 };    ///< ������� ���� ����� ������������ �������� ������
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
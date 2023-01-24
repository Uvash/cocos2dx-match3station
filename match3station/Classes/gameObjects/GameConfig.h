#pragma once
/**
	\addtogroup match3station
	\brief ����� GameCongig ������ ��������� ����������� ��� ����. ������������ � ����, ��� ���� ��� �� � ������� ������ �� �����
*/
///@{
#pragma once

class GameConfig final
{
public:
	const float gameFieldWidth	= 0.75;	///< ������ ���������� ������� ����� � ��������� �� ������ ������
	const float gameFieldHeight	= 1.0;	///< ������ ���������� ������� ����� � ��������� �� ������ ������

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
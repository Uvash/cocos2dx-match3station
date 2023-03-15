/**
    \addtogroup match3station
    \brief ������� ��������� - ����� ����������� ��������� �������� � ���� �������/�������� � ��� �����. �������� ���������� � gameMode
*/
///@{

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

struct gameScore;

class GameUi : public cocos2d::Node
{
protected:
    
    cocos2d::ProgressTimer* hullConditionBar;   ///< ��� �������������� ��������� �������
    cocos2d::ProgressTimer* crewHealthBar;  ///< ��� �������������� ��������� �������� �������
    cocos2d::ProgressTimer* orderBar; ///< ��� �������������� ��������� ������� ����� �������
    cocos2d::ui::Text* scoreText;   ///< ����� ��� ������ ������ ���-�� �����
    
    /**
    \brief ���������� ���, � ������ ��������
    \param[in] spriteName �������� �������, ����������� � ���� ��������
    \details ��������� ���� �������� �������  cocos2d::ProgressTimer � ������ ���������� Timer-�
     **/
    cocos2d::ProgressTimer* prepareTimer(std::string spriteName);

    /**
    \brief ������������� ����� �������� ����, �������� ��� �������� �� ������� ��������
    \param[in] timer ��������� �� ���
    \param[in] percent ������� �������
    \details ��������� ���� �������� �������  cocos2d::ProgressTimer � ������ ���������� Timer-�. ��������� �� ��������� �������� 2 �������
     **/
    void fancySetTimerPercent(cocos2d::ProgressTimer* timer, float percent);
public:
    /**
    \brief ��������� ���������� �����.
    \param[in] score ������ �� ���������� ���-�� �����
     **/
    void updateGameUi(gameScore& score);
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameUi); ///< ������ ��������� ����������� ��� ������ �������
    /**
    \brief �����������
     **/
    GameUi();

    /**
    \brief ����������
     **/
    ~GameUi();
};

///@}
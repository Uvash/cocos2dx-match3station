/**
    \addtogroup match3station
    \brief ���� ����� ���� - ����� �������� �������� ������������� ��� ���������
    ���������� �� ������ 2 ������ - ������ � �����. � ������ �������� ����������� ����� HelloWorldScene 
*/
///@{

#pragma once

#include "cocos2d.h"

class EndGameUi : public cocos2d::Node
{

public:
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameUi); ///< ������ ��������� ����������� ��� ������ �������

    /**
    \brief ����������� ������. ������ ������ ���� ����������� ������
    **/
    EndGameUi();

    /**
    \brief ���������� ������.
    **/
    ~EndGameUi();

    /**
    \brief �������. ���������� ���� ������������ ������ "����� ����"
    **/
    void resetButtonCallback(Ref* pSender);

    /**
    \brief �������. ���������� ���� ������������ ������ "����� �� ����"
    **/
    void exitButtonCallback(Ref* pSender);
};

///@}
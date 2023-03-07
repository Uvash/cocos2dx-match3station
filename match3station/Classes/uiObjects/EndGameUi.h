/**
    \addtogroup match3station
    \brief ���� ����� ���� - ����� �������� �������� ������������� ��� ���������
*/
///@{

#pragma once

#include "cocos2d.h"

class EndGameUi : public cocos2d::Node
{

public:
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameUi); ///< ������ ��������� ����������� ��� ������ �������

    EndGameUi();
    ~EndGameUi();

    void resetButtonCallback(Ref* pSender);
    void exitButtonCallback(Ref* pSender);
};

///@}
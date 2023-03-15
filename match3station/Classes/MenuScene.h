/**
	\addtogroup match3station
	\brief ����� ����� ����. ������ ����� �������� ����
*/
///@{
#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    /**
    \brief ������� �� ��������� ����. 
    \param[in] pSender ���������, �� ���� ��� ������
     **/
    void menuCloseCallback(cocos2d::Ref* pSender);

    /**
    \brief ������� �� ������ MainScene
    \param[in] pSender ���������, �� ���� ��� ������
     **/
    void playCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);    ///< ��������� static create() ��� ������ �����
protected:
    /**
    \brief ��������� ������� � ���
     **/
    void loadSprites();     ///< ��������������� ������� ��� �������� ����� ��������
};
///@}
#include "EndGameUi.h"

#include "gameUi.h"
#include "HelloWorldScene.h"
USING_NS_CC;

EndGameUi::EndGameUi()
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    SpriteFrame* frame = nullptr;
    frame = cache->getSpriteFrameByName("./reset");

    auto buttonReset = MenuItemImage::create();
    buttonReset->setNormalSpriteFrame(cache->getSpriteFrameByName("./reset"));
    buttonReset->setCallback(CC_CALLBACK_1(EndGameUi::resetButtonCallback, this));
    buttonReset->setScale(3.0f);

    auto buttonExit = MenuItemImage::create();
    buttonExit->setNormalSpriteFrame(cache->getSpriteFrameByName("./exit"));
    buttonExit->setCallback(CC_CALLBACK_1(EndGameUi::exitButtonCallback, this));
    buttonExit->setScale(3.0f);

    auto screenSize = Director::getInstance()->getWinSize();

    buttonReset->setPosition({ screenSize.width / 2.0f - 100.0f, screenSize.height / 2.0f });
    buttonExit->setPosition({ screenSize.width / 2.0f + 100.0f, screenSize.height / 2.0f });

    auto menu = Menu::create(buttonReset, buttonExit, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

EndGameUi::~EndGameUi()
{

}

void EndGameUi::resetButtonCallback(Ref* pSender)
{
    auto newScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(newScene);

}

void EndGameUi::exitButtonCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
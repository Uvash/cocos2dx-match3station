#include "MenuScene.h"
#include "MainScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    loadSprites();
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    SpriteFrame* frame = nullptr;

    auto buttonPlay = MenuItemImage::create();
    buttonPlay->setNormalSpriteFrame(cache->getSpriteFrameByName("./MenuButton"));
    buttonPlay->setSelectedSpriteFrame(cache->getSpriteFrameByName("./MenuButtonSelected"));
    buttonPlay->setCallback(CC_CALLBACK_1(MenuScene::playCallback, this));

    auto playText = ui::Text::create({ "Play" }, { "XO_Oriel_Nu.ttf" }, 20.0);
    auto buttonSize = buttonPlay->getContentSize();
    playText->setPosition({ buttonSize.width / 2.0f, buttonSize.height / 2.0f });
    buttonPlay->addChild(playText);


    auto buttonExit = MenuItemImage::create();
    buttonExit->setNormalSpriteFrame(cache->getSpriteFrameByName("./MenuButton"));
    buttonExit->setSelectedSpriteFrame(cache->getSpriteFrameByName("./MenuButtonSelected"));
    buttonExit->setCallback(CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

    auto exitText = ui::Text::create({ "Exit" }, { "XO_Oriel_Nu.ttf" }, 20.0);
    buttonSize = buttonExit->getContentSize();
    exitText->setPosition({ buttonSize.width / 2.0f, buttonSize.height / 2.0f });
    buttonExit->addChild(exitText);


    buttonPlay->setPosition({ visibleSize.width / 2.0f, visibleSize.height / 2.0f + 100.0f });
    buttonExit->setPosition({ visibleSize.width / 2.0f, visibleSize.height / 2.0f - 100.0f });

    float scale = visibleSize.width / (3.0f * buttonSize.width);
    buttonPlay->setScale(scale);
    buttonExit->setScale(scale);

    auto menu = Menu::create(buttonPlay, buttonExit, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    auto sprite = Sprite::create("SpaceBackGround_by_Rawdanitsu/image4.jpg");
    if (sprite == nullptr)
    {
        throw std::runtime_error("failed to loas SpaceBackGround_by_Rawdanitsu/image4.jpg");
    }
    // position the sprite on the center of the screen
    sprite->setAnchorPoint({ 0, 0 });
    auto backGroundSize{sprite->getContentSize()};
    Vec2 scaleCandidats{ visibleSize.width / backGroundSize.width , visibleSize.height / backGroundSize.height};
    float scaleForScreen = std::max(scaleCandidats.y, scaleCandidats.x);
    sprite->setScale(scaleForScreen);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    /*
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"

    */

    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MenuScene::playCallback(cocos2d::Ref* pSender)
{
    auto newScene = MainScene::createScene();
    Director::getInstance()->replaceScene(newScene);
}

void MenuScene::loadSprites()
{
    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("uvash.plist");
}


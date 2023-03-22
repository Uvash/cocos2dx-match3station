#include "gameUi.h"
#include "..\gameObjects\HelpStructures.h"
#include <algorithm>


USING_NS_CC;

void GameUi::updateGameUi(gameScore& score)
{
	hullConditionBar->stopAllActions();
	crewHealthBar->stopAllActions();
	orderBar->stopAllActions();

	auto progressTo = ProgressTo::create(2.0f, 100.0f);
	hullConditionBar->runAction(progressTo);
	crewHealthBar->runAction(progressTo);
	orderBar->runAction(progressTo);

	fancySetTimerPercent(hullConditionBar, score.hullCondition);
	fancySetTimerPercent(crewHealthBar, score.crewHealth);
	fancySetTimerPercent(orderBar, score.order);

	scoreText->setString(std::to_string(score.score));

}

void GameUi::fancySetTimerPercent(cocos2d::ProgressTimer* timer, float percent)
{
	if (!timer)
		return;

	timer->stopAllActions();
	auto progressTo = ProgressTo::create(2.0f, percent);
	timer->runAction(progressTo);
}

cocos2d::ProgressTimer* GameUi::prepareTimer(std::string spriteName)
{
	cocos2d::ProgressTimer* timer = nullptr;
	//Вытаскиваем спрайты из кэша
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	//Создаём 3 шкалы со своими спрайтами
	Sprite* spriteBar = Sprite::create();
	spriteBar->setSpriteFrame(cache->getSpriteFrameByName(spriteName));
	timer = ProgressTimer::create(spriteBar);

	timer->setType(ProgressTimer::Type::BAR);
	timer->setPercentage(100.0f);
	timer->setAnchorPoint({ 0.0f, 0.0f });
	timer->setMidpoint({ 0.0f, 0.0f });
	timer->setBarChangeRate({ 1.0f, 0.0f });
	timer->setRotation(-90.0f);
	addChild(timer);
	return timer;
}

GameUi::GameUi()
{

	auto screenSize = Director::getInstance()->getWinSize();
	cocos2d::Vec2 possibleBarSize = { (screenSize.width * 0.25f - 50.0f ) / 3, screenSize.height * 0.5f - 50.0f};
	cocos2d::Vec2 newPosition = { screenSize.width * 0.75f , screenSize.height * 0.5f };

	//Вытаскиваем спрайты из кэша
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	
	//Подготавливаем полоски
	hullConditionBar = prepareTimer("./barEng");
	crewHealthBar = prepareTimer("./barMed");
	orderBar = prepareTimer("./barSec");

	//Определяем размер одной полоски
	auto barSize = hullConditionBar->getContentSize();
	//Поскольку мы поворачиваем полоску, нам надо учитывать этот поворот в соотношениях
	cocos2d::Vec2	scaleCandidate = { possibleBarSize.x / barSize.height , possibleBarSize.y / barSize.width };
	float scale = std::min( scaleCandidate.x , scaleCandidate.y);
	if (scale > 1.0f)
	{
		//Корректируем размер от экрана
		hullConditionBar->setScale(scale);
		crewHealthBar->setScale(scale);
		orderBar->setScale(scale);
	}

	//Устанавливаем на место
	hullConditionBar->setPosition({ newPosition.x + possibleBarSize.x * 1.0f, newPosition.y });
	crewHealthBar->setPosition({ newPosition.x + possibleBarSize.x * 2.0f, newPosition.y });
	orderBar->setPosition({ newPosition.x + possibleBarSize.x * 3.0f, newPosition.y });

	scoreText = ui::Text::create({ "000000" }, { "XO_Oriel_Nu.ttf" }, 20.0);
	newPosition = { screenSize.width * 0.75f + screenSize.width * (0.25f / 2.0f), screenSize.height * 0.45f };
	scoreText->setPosition(newPosition);
	addChild(scoreText);
}

GameUi::~GameUi() {}
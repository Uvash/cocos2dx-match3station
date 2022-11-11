#pragma once

#include "cocos2d.h"
#include <functional>
#include "ui/UIWidget.h"
#include "HelpStructures.h"

enum class FigureType
{
	CMO,
	CE,
	HOS,
	maxFigure
};

enum class FigureStatus
{
	normal,
	choosen,
	deleted,
	moving,
	maxStatus
};

class GameMode;
class GameFigure : public cocos2d::ui::Widget
{
public:
	Node* getVirtualRenderer() override;
	void copySpecialProperties(Widget* model) override;
	const cocos2d::Size& getContentSize() const override;

	void setScreenPosition(const cocos2d::Vec2& pos);
	void jumpAndFall(cocos2d::Vec2 jumpPosition, cocos2d::Vec2 targetPosition);

	const point2i& getCoordinats();
	void setCoordinats(const point2i& target);

	void setFigureType(FigureType type);
	void setFigureStatus(FigureStatus gStatus);
	inline FigureType getFigureType() { return gameType; }
	inline FigureStatus getFigureStatus() { return gameStatus;  }
protected:
	FigureStatus gameStatus = FigureStatus::normal;
	FigureType gameType = FigureType::CMO;
	cocos2d::Sprite* sprite = nullptr;
	point2i coordinats = { 0, 0 };
	GameMode& gameMode;
public:
	static GameFigure* create(GameMode& mode);

	bool init() override;
	void initRenderer() override;

	GameFigure() = default;
	GameFigure(GameMode & mode);
	~GameFigure() override;
public:
	void setChoosen();
	void setNormal();
	void setDeleted();
	void setMoving();
};

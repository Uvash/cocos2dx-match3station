#pragma once

#include "cocos2d.h"
#include <functional>
#include "ui/UIWidget.h"
#include "HelpStructures.h"

enum class FigureType
{
	assistant,
	CMO,
	CE,
	HOS,
	maxFigure
};

class GameField;
class GameFigure : public cocos2d::ui::Widget
{
public:
	GameFigure() = default;
	GameFigure(GameField& field);
	~GameFigure() override;

	bool init() override;
	void initRenderer() override;
	Node* getVirtualRenderer() override;
	void copySpecialProperties(Widget* model) override;
	const cocos2d::Size& getContentSize() const override;

	void setScreenPosition(const cocos2d::Vec2& pos);

	const point2i& getCoordinats();
	void setCoordinats(const point2i& target);

protected:
	FigureType gameType = FigureType::assistant;
	cocos2d::Sprite* sprite = nullptr;
	point2i coordinats = { 0, 0 };
	GameField& master;

public:
	static GameFigure* create(GameField& field);
};

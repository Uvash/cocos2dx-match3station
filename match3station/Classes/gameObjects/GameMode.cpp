#include "GameMode.h"
#include "GameFigure.h"
#include "GameField.h"
#include <random>



GameMode::GameMode(GameField& gField) : gameField{ gField }
{

}
GameMode::~GameMode()
{

}

void GameMode::fillField()
{
	std::random_device rd;
	std::mt19937 gen(rd());  
	std::uniform_int_distribution<> dist(0, (int)(FigureType::maxFigure) - 1);


	int i = 0;
	std::for_each(gameField.content.begin(), gameField.content.end(), [&gen, &dist, &i, this](GameFigure* &pFigure)
		{
			GameFigure* figure = GameFigure::create(*this);
			if (figure == nullptr)
				throw std::exception{"GameMode can`t create figure in fillField"};

			switch (dist(gen))
			{
				case(0): {figure->setFigureType(FigureType::CMO); break; }
				case(1): {figure->setFigureType(FigureType::CE); break; }
				case(2): {figure->setFigureType(FigureType::HOS); break; }
			}

			auto iter = gameField.content.begin() + i;
			gameField.addFigure(figure, iter);
			gameField.addChild(figure);
			//figure->setAnchorPoint({0.0f, 0.0f});
			i++;
		});
}

void GameMode::clickCallback(GameFigure* figure)
{
	if (figure == nullptr)
	{
		throw std::runtime_error("GameField: Try to call target nullptr");
		return;
	}

	if (clicked == nullptr)
	{
		clicked = figure;
		clicked->setFigureStatus(FigureStatus::choosen);
		return;
	}

	if (clicked == figure)
	{
		clicked->setFigureStatus(FigureStatus::normal);
		clicked = nullptr;
		return;
	}

	gameField.swapFigure(clicked->getCoordinats(), figure->getCoordinats());
	clicked->setFigureStatus(FigureStatus::normal);
	figure->setFigureStatus(FigureStatus::normal);
	clicked = nullptr;
}

bool GameMode::init()
{
	fillField();
	return true;
}

GameMode* GameMode::create(GameField& field)
{
	GameMode* pRect = new(std::nothrow) GameMode(field);
	if (pRect && pRect->init())
	{
		pRect->autorelease();
		return pRect;
	}
	else
	{
		delete pRect;
		pRect = nullptr;
		return pRect;
	}
}
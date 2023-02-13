#include "GameMode.h"
#include "GameFigure.h"
#include "GameField.h"

#include "../uiObjects/gameUi.h"
#include <random>
#include <stdexcept>



GameMode::GameMode(GameField& field, GameUi& ui) : gameField{ field }, gameUi{ ui }
{
	collumFlags.resize(gameField.size.w, false);
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
				throw std::runtime_error{std::string{"GameMode can`t create figure in fillField"}};

			auto iter = gameField.content.begin() + i;
			figure->setFigureType(getRandomFigureType());
			gameField.addFigure(figure, iter);
			gameField.addChild(figure);
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

	if (figure->getFigureStatus() == FigureStatus::deleted || figure->getFigureStatus() == FigureStatus::moving)
	{
		return;
	}

	if (lockFigureCount > 0)
	{
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

	clicked->setFigureStatus(FigureStatus::normal);

	gameField.swapFigure(clicked->getCoordinats(), figure->getCoordinats());
	gameField.moveToHomeOnScreen(clicked->getCoordinats());
	gameField.moveToHomeOnScreen(figure->getCoordinats());
	clicked = nullptr;
}

void GameMode::checkCombination(point2i position)
{
	if (!gameField.checkScopeField(position))
		return;
	auto targetType = gameField.getFiureType(position);
	std::vector<point2i> leftRow = getFigureSameTypeOnTowards(targetType, position, { -1, 0 });
	std::vector<point2i> rightRow = getFigureSameTypeOnTowards(targetType, position, { 1, 0 });
	std::vector<point2i> downCollum = getFigureSameTypeOnTowards(targetType, position, { 0, -1 });
	std::vector<point2i> upCollum = getFigureSameTypeOnTowards(targetType, position, { 0, 1 });
	
	//������� ������ ������� � ������ ���� � ������
	leftRow.reserve(leftRow.size() + rightRow.size());
	leftRow.insert(leftRow.end(), rightRow.begin(), rightRow.end());

	downCollum.reserve(downCollum.size() + upCollum.size());
	downCollum.insert(downCollum.end(), upCollum.begin(), upCollum.end());

	bool needProcessStart = true;	//Нужно ли обработать центральную фигурку
	auto processFunction = [this](point2i& target)
	{
		auto figure = this->gameField.getFigureFromField(target);
		collumFlags[figure->getCoordinats().x] = true;
		figure->setFigureStatus(FigureStatus::deleted);
	};

	// +1 поскольку мы не учитывали стартовую точку
	if (leftRow.size() + 1 >= rowRequestToCombination)
	{
		needProcessStart = false; //Закидываем центральную фигурку в обработку на удаление
		leftRow.push_back(position);
		std::for_each(leftRow.begin(), leftRow.end(), processFunction);
		calculateScore(targetType, leftRow.size() + 1);
	}

	if (downCollum.size() + 1 >= rowRequestToCombination)
	{
		if(needProcessStart)
			downCollum.push_back(position);
		std::for_each(downCollum.begin(), downCollum.end(), processFunction);
		calculateScore(targetType, leftRow.size() + 1);
	}
}

void GameMode::updateCollum()
{
	std::vector<point2i> movingFigure; ///< Движение фигур мы запустим когда после всего

	for (std::vector <bool>::iterator iter = collumFlags.begin(); iter != collumFlags.end(); iter++)
	{
		if (!(*iter))
			continue;	
		
		auto distance = std::distance(collumFlags.begin(), iter);
		
		auto mapIter = gameField.content.begin();
		mapIter += distance;
		
		while (true)
		{
			auto deletedCandidate = mapIter;
			if (!gameField.findNextWithCurrentStatus(deletedCandidate, FigureStatus::deleted, gameField.size.w))	///< Сдвиг по ширене = +1 наверх
			{
				break; 
			}
			auto aliveCandidate = deletedCandidate;
			if (!gameField.findNextWithCurrentStatus(deletedCandidate, FigureStatus::normal, gameField.size.w))
			{
				break; 
			}

			gameField.swapFigure(aliveCandidate, deletedCandidate);
			movingFigure.push_back((*aliveCandidate)->getCoordinats());
			///< Удалённую фигурку не двигаем, поскольку её передвижение будет позже
		}

		*iter = false;
	}

	if (!movingFigure.empty())
	{
		for (auto figure : movingFigure)
		{
			gameField.moveToHomeOnScreen(figure);
		}
	}
}

void GameMode::replaceDeleted()
{
	auto func = [this](GameFigure* figure)
	{
		if (figure->getFigureStatus() != FigureStatus::deleted)
			return;

		figure->setFigureStatus(FigureStatus::normal);
		figure->setFigureType(getRandomFigureType());

		gameField.replaceFigure(figure->getCoordinats());
	};

	std::for_each(gameField.content.begin(), gameField.content.end(), func);
}

void GameMode::endMoveCallback(point2i position)
{
	//checkFiguresReqest.insert(position);
	needCheckFigureSet.insert(position);
}

FigureType GameMode::getRandomFigureType()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, (int)(FigureType::maxFigure)-1);

	FigureType choosen;
	switch (dist(gen))
	{
		case(0): {choosen = FigureType::CMO; break; }
		case(1): {choosen = FigureType::CE; break; }
		case(2): {choosen = FigureType::HOS; break; }
	}
	return choosen;
}

std::vector<point2i> GameMode::getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset)
{
	std::vector<point2i> result;
	point2i currentPoint = startPosition + offset;

	while(gameField.checkScopeField(currentPoint))
	{
		if (!gameField.checkScopeField(currentPoint))
			break;
		if (gameField.getFiureType(currentPoint) != searchType)
			break;

		result.push_back(currentPoint);
		currentPoint = currentPoint + offset;
	}
	return result;
}

void GameMode::calculateScore(FigureType figureType, int figureCount)
{
	int scoreCount = figureCount * (5.0f * (figureCount + 1));	///< здесь используем арифмитическую прогрессию
	switch (figureType)
	{
		case(FigureType::CMO)	: {score.addCrewHealth(figureCount); break; }
		case(FigureType::CE)	: {score.addHullCondition(figureCount); break; }
		case(FigureType::HOS)	: {score.addOrder(figureCount); break; }
	}
	score.score += scoreCount;
}

void GameMode::generateEvents()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> typeDist(0, (int)(FigureType::maxFigure)-1);
	std::uniform_int_distribution<> criticalFailDistr(0, 9);
	std::uniform_int_distribution<> damageDistr(0, 10);

	int damage = -1 * damageDistr(gen);
	if (criticalFailDistr(gen) == 0)
		damage *= 2;

	FigureType choosen;
	switch (typeDist(gen))
	{
		case((int)FigureType::CMO):	{score.addCrewHealth(damage); break; }
		case((int)FigureType::CE):	{score.addHullCondition(damage); break; }
		case((int)FigureType::HOS):	{score.addOrder(damage); break; }
	}
}

bool GameMode::init()
{
	fillField();
	return true;
}


GameMode* GameMode::create(GameField& field, GameUi& ui)
{
	GameMode* pRect = new(std::nothrow) GameMode(field, ui);
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

void GameMode::addLockFigure()
{
	lockFigureCount++;
}

void GameMode::removeLockFigure()
{
	lockFigureCount--;
	if (lockFigureCount <= 0)
	{
		checkFigureFromSet();
		updateCollum();
		replaceDeleted();
		generateEvents();
		gameUi.updateGameUi(score);
	}
}

void GameMode::checkFigureFromSet()
{
	for (auto figure : needCheckFigureSet)
	{
		checkCombination(figure);
	}
	needCheckFigureSet.clear();
}
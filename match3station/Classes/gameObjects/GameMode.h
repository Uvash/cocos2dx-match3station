/**
	\addtogroup match3station
	\brief Класс Режим игры. Определяет логику и правила игры
*/
///@{
#pragma once
#include "cocos2d.h"
#include "HelpStructures.h"

#define CURENT_STATUS 0
#define PREVIOUS_STATUS 1
#define STATUS_SIZE 2

class GameField;
class GameFigure;
class point2i;
enum class FigureType;

class GameUi;

class GameMode : public cocos2d::Node ///< Наследуемся от ноды, дабы соответствовать дао движка
{
public:
	void fillField();							///< Заполняет поле фигурками
	void clickCallback(GameFigure* figure);		///< Каллбек вызываемый при клике на фигурку
	void checkCombination(point2i position);	///< Проверяем комбинацию для двумерной позиции
	void updateCollum();						///< Пробегает по столбцам, сдвигая удалённые фигурки на верх (а верхние "бросая" в низ)
	void replaceDeleted();						///< Обновляет удалённые фигурки.
	void endMoveCallback(point2i position);		///< Вызывается фигуркой после завершения движения
	FigureType getRandomFigureType();			///< Генерирует случайный тип фигурки
protected:
	GameUi& gameUi;								///< Ссылка на худ
	gameScore score;							///< Количество очков
protected:
	GameField& gameField;						///< Ссылка на игровое поле
	GameFigure* clicked = nullptr;				///< Указатель на выбранную фигурку
	std::vector<point2i> getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset); ///< Возвращает массив фигурок такого же типа как и исходная
	void calculateScore(FigureType figureType, int figureCount);	///< Подсчитывает количество очков
	void generateEvents();						///< Создаёт события наносящие вред станции

	int rowRequestToCombination = 3;		///< Кол-во фигурок необходимое в ряд
	//int collumRequestToCombination = 3;		///< Кол-во фигурок необходимое в столбец

	std::vector <bool> collumFlags;			///< Вспомогательный вектор, для хранения флагов столбцов, отмечающих необходимость их обновления
protected:
	void playSoundEffect(const char* fileName);	///< Проигрывает звуковой файл формат mp3

public:
	GameMode(GameField& field, GameUi& ui);
	~GameMode() override;

	bool init() override;							///< Вспомогательный метод для Node
	static GameMode* create(GameField& field, GameUi& ui);		///< Вспомогательный метод для Node
public:
	void addLockFigure();		///< Увеличивает lockFigureCount на 1
	void removeLockFigure();	///< Уменьшает lockFigureCount на 1
protected:
	int lockFigureCount = 0;	///< Костыль для подсчёта фигур которые двигаются
	std::set<point2i> needCheckFigureSet; ///< Дерево, для хранения координат фигур которые нужно проверить
	void checkFigureFromSet();		///< Проверить все фигуры в дереве

	void endGame();	///< Вызывается по завершению игры
	void checkScore(); ///< Проверяет кол-во очков
};
///@}
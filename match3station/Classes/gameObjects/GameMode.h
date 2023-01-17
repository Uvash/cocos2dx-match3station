/**
	\addtogroup match3station
	\brief Класс Режим игры. Определяет логику и правила игры
*/
///@{
#pragma once
#include "cocos2d.h"

#define CURENT_STATUS 0
#define PREVIOUS_STATUS 1
#define STATUS_SIZE 2

class GameField;
class GameFigure;
class point2i;
enum class FigureType;

enum class GameModeStatus	///< Описываем статусы Игрового Режима как конечный автомат с хранение преведущего состояния
{
	normal = 0,				///< Всё хорошо ожидаем ввод от игрока
	moving = 1,
	swap = 2,				///< Идёт обмен фигурок
	checkCombination = 3,	///< Проверка после хода
	updateCollum = 4,		///< Обновляем столбцы, поднимая "удалённые" фигурки наверх, и скидывая "живые" вниз
	replaceDeleted = 5		///< Заменяет "удалённые" фигурки на новые
};

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
	GameField& gameField;						///< Ссылка на игровое поле
	GameFigure* clicked = nullptr;				///< Указатель на выбранную фигурку
	std::vector<point2i> getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset); ///< Возвращает массив фигурок такого же типа как и исходная

	int rowRequestToCombination = 3;		///< Кол-во фигурок необходимое в ряд
	int collumRequestToCombination = 3;		///< Кол-во фигурок необходимое в столбец

	std::vector <bool> collumFlags;			///< Вспомогательный вектор, для хранения флагов столбцов, отмечающих необходимость их обновления

	std::array< GameModeStatus, STATUS_SIZE > statusList = { GameModeStatus::normal, GameModeStatus::normal }; ///< Вспомогательный массив из 2-х элементов для хранения текущего [ 0 ] и преведущего [ 1 ] статуса.
	void setNextStatus(GameModeStatus nextStatus);

public:
	GameMode(GameField &gField);
	~GameMode() override;

	bool init() override;							///< Вспомогательный метод для Node
	static GameMode* create(GameField& field);		///< Вспомогательный метод для Node
public:
	void addLockFigure();		///< Увеличивает lockFigureCount на 1
	void removeLockFigure();	///< Уменьшает lockFigureCount на 1
protected:
	int lockFigureCount = 0;	///< Костыль для подсчёта фигур которые двигаются
	std::set<point2i> needCheckFigureSet; ///< Дерево, для хранения координат фигур которые нужно проверить
	void checkFigureFromSet();		///< Проверить все фигуры в дереве
};
///@}
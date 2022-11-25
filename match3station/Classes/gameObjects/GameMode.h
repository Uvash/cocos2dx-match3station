/**
	\addtogroup match3station
	\brief Класс Режим игры. Определяет логику и правила игры
*/
///@{
#pragma once
#include "cocos2d.h"

class GameField;
class GameFigure;
class point2i;
enum class FigureType;

class GameMode : public cocos2d::Node ///< Наследуемся от ноды, дабы соответствовать дао движка
{
public:
	void fillField();							///< Заполняет поле фигурками
	void clickCallback(GameFigure* figure);		///< Каллбек вызываемый при клике на фигурку
	void checkCombination(point2i position);	///< Проверяем комбинацию для двумерной позиции
	void updateCollum();						///< Пробегает по столбцам, сдвигая удалённые фигурки на верх (а верхние "бросая" в низ)
	void replaceDeleted();						///< Обновляет удалённые фигурки.
	FigureType getRandomFigureType();			///< Генерирует случайный тип фигурки
protected:
	GameField& gameField;						///< Ссылка на игровое поле
	GameFigure* clicked = nullptr;				///< Указатель на выбранную фигурку
	std::vector<point2i> getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset); ///< Возвращает массив фигурок такого же типа как и исходная

	int rowRequestToCombination = 3;		///< Кол-во фигурок необходимое в ряд
	int collumRequestToCombination = 3;		///< Кол-во фигурок необходимое в столбец

	std::vector <bool> collumFlags;			///< Вспомогательный вектор, для хранения флагов столбцов, отмечающих необходимость их обновления 
public:
	GameMode(GameField &gField);
	~GameMode() override;

	bool init() override;							///< Вспомогательный метод для Node
	static GameMode* create(GameField& field);		///< Вспомогательный метод для Node
};
///@}
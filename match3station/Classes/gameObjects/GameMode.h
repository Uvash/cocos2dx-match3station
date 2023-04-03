/**
	\addtogroup match3station
	\brief Класс GameMode. Определяет логику и правила игры

	\details Взаимодействует с gameUi, gameField и GameConfig. Нуждается в ссылках на первые два класса. Наследуеться от Node, дабы соответствовать дао движка
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

class GameMode : public cocos2d::Node
{
public:
	/**
	\brief Заполняет поле случайными фигурками
	**/
	void fillField();

	/**
	\brief Каллбек вызываемый при клике на фигурку
	\param[in] figure указатель на фигурку
	**/
	void clickCallback(GameFigure* figure);

	/**
	\brief Проверяем комбинацию в данной точке
	\param[in] position двумерные (игровые) координаты которые надо проверить
	**/
	void checkCombination(point2i position);

	/**
	\brief Пробегает по столбцам, сдвигая удалённые фигурки наверх (а верхние "бросая" в низ)
	**/
	void updateCollum();

	/**
	\brief Обновляет удалённые фигурки. Заменяя их новыми
	**/
	void replaceDeleted();

	/**
	\brief Вызывается фигуркой после завершения движения. Разблокирует клики по фигуркам.
	\param[in] position двумерные (игровые) координаты фигурки окончившей движение
	**/
	void endMoveCallback(point2i position);

	/**
	\brief Генерирует случайный тип фигурки.
	**/
	FigureType getRandomFigureType();
protected:
	GameUi& gameUi;								///< Ссылка на худ
	gameScore score;							///< Количество очков
protected:
	GameField& gameField;						///< Ссылка на игровое поле
	GameFigure* clicked = nullptr;				///< Указатель на выбранную фигурку

	/**
	\brief Возвращает массив фигурок нужного типа по заданному направлению и двумерным (игровым) координатам 
	\param[in] searchType тип фигурки который ищем
	\param[in] startPosition стартовая позиция в двумерных (игровых) координатах
	\param[in] offset смещение до следующей фигурки в двумерных (игровых) координатах
	\return вектор фигурок, которые мы нашли по заданным параметрам

	\details Решение разместить этот метод тут, а не в GameField обусловленно, тем что метод каким мы будем искать фигурки зависит от режима игры, а не от карты.
	**/
	std::vector<point2i> getFigureSameTypeOnTowards(FigureType searchType, point2i startPosition, point2i offset); ///< Возвращает массив фигурок такого же типа как и исходная

	/**
	\brief Подсчитывает количество очков и очков ремонта в зависимости от типа фигурок
	\param[in] figureType тип уничтоженных фигурок
	\param[in] figureCount количество уничтоженных фигурок
	**/
	void calculateScore(FigureType figureType, int figureCount);

	/**
	\brief Создаёт события наносящие вред станции. 
	\details Просто уменьшает прочность одной из полосок
	**/
	void generateEvents();

	int rowRequestToCombination = 3;		///< необходимое количество фигурок для создания комбинации

	std::vector <bool> collumFlags;			///< Вспомогательный вектор, для хранения флагов столбцов, отмечающих необходимость их обновления
protected:
	/**
	\brief Проигрывает звуковой файл формат mp3
	\param[in] fileName название файла
	\details Обёртка над методом вызова звуков из движка. Здесь задаёться название файла, громкость храниться в GameConfig
	**/
	void playSoundEffect(const char* fileName);	///< Проигрывает звуковой файл формат mp3

public:
	/**
	\brief конструктор класса
	\param[in] field ссылка на игровое поле
	\param[in] ui ссылка на пользовательский интерфейс
	**/
	GameMode(GameField& field, GameUi& ui);

	/**
	\brief деструктор класса
	**/
	~GameMode() override;

	/**
	\brief Инициализатор. Вызывается после конструктора движком.
	**/
	bool init() override;

	/**
	\brief Метод вызываемый движком для создания класса.
	\details Поскольку стандартный конструктор нам не подходит, то и стандартным макросом мы не отделаемся.
	**/
	static GameMode* create(GameField& field, GameUi& ui);		///< Вспомогательный метод для Node
public:
	/**
	\brief Увеличивает lockFigureCount на 1
	\details lockFigureCount больше нуля блокирует обработку кликов по фигуркам.
	**/
	void addLockFigure();
	/**
	\brief Уменьшает lockFigureCount на 1 производит проверки если lockFigureCount = 0
	\details В случаи возвращения всех фигурок на свои места разблокирует клики, и за одно проверяет наличие выпавших комбинаций
	**/
	void removeLockFigure();
protected:
	int lockFigureCount = 0;	///< Костыль для подсчёта фигур которые двигаются

	std::set<point2i> needCheckFigureSet; ///< Дерево, для хранения координат фигур которые нужно проверить

	/**
	\brief Проверить все фигуры в дереве
	\details В дерево фигуры попадают после окончания движения. После чего все они проверяются на возможные комбинации
	**/
	void checkFigureFromSet();		///< Проверить все фигуры в дереве

	/**
	\brief Вызываеться если игрок проиграл
	**/
	void endGame();
	/**
	\brief Проверяет состояние станции
	**/
	void checkScore();
};
///@}

/**
    \addtogroup match3station
    \brief Игровое Поле - класс описывающий игровое поле на котором располагаются фигуры
*/
///@{
#pragma once

#include "cocos2d.h"
#include <vector>
#include "HelpStructures.h"

class GameFigure;
class GameMode;
enum class FigureType;
enum class FigureStatus;
class GameField: public cocos2d::Node
{
    friend GameMode;

public:
    void addFigure(GameFigure* pfigure, std::vector<GameFigure*>::iterator iterAddres); ///< Добавляет указатель фигуры в таблицу (поле) по итератору
    GameFigure* getFigureFromField(point2i target); ///< Получить указатель фигуры по двумерным координатам
    void replaceFigure(point2i position);   ///< Заменяет фигурку на случайную и воспроизводит её падение сверху
protected:
    point2i size = {5, 5 }; ///< Размер поля
    int spriteSize = 64;    ///< Размер спрайта
    std::vector<GameFigure*> content;   ///< Вектор для хранения указателей

    void swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt); ///< меняет фигуры по итератору
    void swapFigure(point2i first, point2i second); ///< меняет фигуры по двумерным координатам

protected:
    bool moveIterator(std::vector<GameFigure*>::iterator& iter, size_t offset); ///< Сдвигает полученный итератор на указанное значение
public:
    bool findNextWithCurrentStatus(std::vector<GameFigure*>::iterator& iter, FigureStatus searchStatus, size_t offset); ///< пытаеться найти фигуру с нужным статусом по направлению

    void allocField();
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField); ///< Макрос создающий необходимые для движка функции

    // Вспомогательные функции для преобразования одномерных координат массива в двумерные игровые
    bool checkScopeField(point2i target);   ///< Проверяет корректность двумерных координат
    bool checkScopeField(size_t target);    ///< Проверяет корректность одномерных координат
    bool checkScopeField(std::vector<GameFigure*>::iterator target); ///< Проверяет корректность итератора
    cocos2d::Vec2 getScreenPositionFrom2i(point2i target); ///< Вычисляет координаты в пиксилях по координатам на игровом поле
    //Не самое правильное решение возиться с преобразованием size_t <-> int, но пока что оставим так
    inline int getFigureAddressFromFieldCoordinats(point2i target); ///< Преобразует двумерные координаты поля в одномерные 
    inline point2i getFieldCoordinatsFromFigureAddress(int address);///< Преобразует одномерные координаты поля в двумерные 
    FigureType getFiureType(point2i address, point2i offset = {0, 0}); ///< Возвращает тип фигуры по двумерным координатам
public:
    GameField();
    ~GameField() override;
    bool init() override;
};
///@}

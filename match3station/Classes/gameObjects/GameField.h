
/**
    \addtogroup match3station
    \brief Игровое Поле - класс описывающий игровое поле на котором располагаются фигуры

    \details Хранит и управляет фигурами (сдвиг перестановка и т.д.) в векторе. Работает как с одномерными координатами для вектора, так и с двумерными для самой игры. 
    Большая часть методов работает или с одномерными координатам / итераторами на вектор или же с двумарными игровыми координатами. Друг GameMode необходим для уменьшения издержек на доступ к вектору фигурок.
*/
///@{
#pragma once

#include "cocos2d.h"
#include <vector>
#include "HelpStructures.h"

class GameFigure;
class GameMode;
class GameConfig;

enum class FigureType;
enum class FigureStatus;

class GameField: public cocos2d::Node
{
    friend GameMode;

public:
    /**
    \brief Добавляет указатель фигуры в таблицу (поле) по итератору
    \param[in] pfigure указатель на добавляемую фигуру
    \param[in] iterAddres Итератор вектора, в который будем помещать данный указатель
    **/
    void addFigure(GameFigure* pfigure, std::vector<GameFigure*>::iterator iterAddres);

    /**
    \brief Получить указатель фигуры по двумерным координатам
    \param[in] target двумерный адрес фигуры
    \return Указатель на фигуру, по этому адресу или nullptr если преобразование не удалось
    **/
    GameFigure* getFigureFromField(point2i target); ///< Получить указатель фигуры по двумерным координатам

    /**
    \brief Заменяет фигурку на случайную и воспроизводит её падение сверху
    \param[in] position двумерный адрес фигуры
    **/
    void replaceFigure(point2i position);
protected:
    cocos2d::Size screenSize;   ///< Размеры поля от экрана
    point2i size = {5, 5 }; ///< Размер поля
    std::vector<GameFigure*> content;   ///< Вектор для хранения указателей

    /**
    \brief Меняет фигуры местами по итераторам
    \param[in] firstIt  первый итератор
    \param[in] secondIt второй итератор
    \warning Не проверяет валидность итератора
    **/
    void swapFigure(std::vector<GameFigure*>::iterator firstIt, std::vector<GameFigure*>::iterator secondIt);

    /**
    \brief Меняет фигуры местами по двумерным (игровым) координатам
    \param[in] first первая позиция
    \param[in] secondIt вторая позиция
    \warning Не проверяет валидность координат
    **/
    void swapFigure(point2i first, point2i second);

    /**
    \brief Двигает фигуру (находящуюся в ячейке игровых координат), в "домашнуюю" позицию на экране
    \param[in] position игровые координаты фигуры
    **/
    void moveToHomeOnScreen(point2i position); 

protected:
    /**
    \brief Сдвигает полученный итератор на указанное значение
    \param[in] iter итератор вектора, где храняться фигуры
    \param[in] offset смещение итератора
    \return возвращает флаг успешности сдвига. При не успешности валидность итератора не гарантируеться
    \warning Может испортить итератор
    **/
    bool moveIterator(std::vector<GameFigure*>::iterator& iter, size_t offset);
public:

    /**
    \brief Пытаеться найти фигуру с нужным статусом по направлению
    \param[in] iter Стартовая позиция итератора, где храняться фигуры.
    \param[in] searchStatus Тип искомой фигуры
    \param[in] offset Смещение (направление) в котором ведёться поиск внутри вектора
    \param[out] iter Итератор на фигуру с искомым статусом. Валиден, если функция вернула true
    \return возвращает флаг успешности поиска. При не успешности валидность итератора не гарантируеться
    \warning Может испортить итератор
    **/
    bool findNextWithCurrentStatus(std::vector<GameFigure*>::iterator& iter, FigureStatus searchStatus, size_t offset); ///< 

    /**
    * \brief Вспомогательная функция для выделения нужного кол-ва памяти под вектор
    **/
    void allocField();
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameField); ///< Макрос создающий необходимые для движка функции

    // Вспомогательные функции для преобразования одномерных координат массива в двумерные игровые
    /**
    \brief Проверяет корректность двумерных (игровых) координат.
    \param[in] target Двумерные (игровые) координаты
    \return флаг валидности этих координат
    **/
    bool checkScopeField(point2i target);   ///< Проверяет корректность двумерных координат

    /**
    \brief Проверяет корректность одномерных (векторных) координат
    \param[in] target Одномерные (векторные) координаты
    \return флаг валидности этих координат
    **/
    bool checkScopeField(size_t target);

    /**
    \brief Проверяет корректность итератора, для вектора с фигурами
    \param[in] target Итератор вектора
    \return флаг валидности этих координат
    **/
    bool checkScopeField(std::vector<GameFigure*>::iterator target);

    /**
    \brief Выдаёт по игровым координатом позицию фигурки на экране
    \param[in] target игровые координаты
    \return двумерные координаты на экране
    \warning Не проверяет валидность игровых координат
    **/
    cocos2d::Vec2 getScreenPositionFrom2i(point2i target);

    //Не самое правильное решение возиться с преобразованием size_t <-> int, но пока что оставим так
    /**
    \brief Преобразует двумерные (игровые) координаты в одномерные (векторные).
    \param[in] target двумерные (игровые) координаты
    \return одномерные координаты вектора фигурок
    \warning Не проверяет валидность игровых координат. То есть преобразование (-3, 1) -> (2) допустимо.
    \warning Возвращаемый тип имеет значение int. Возможны проблемы при создании поля большего sizeof(int) но ещё допустимого для size_t Но мы ведь не будем так делать?
    **/
    inline int getFigureAddressFromFieldCoordinats(point2i target); ///< Преобразует двумерные координаты поля в одномерные 
    
    /**
    \brief Преобразует одномерные (векторные) координаты в двумерные (игровые)
    \param[in] target одномерные (векторные)
    \return двумерные (игровые) координаты
    \warning Входящий тип имеет значение int. Возможны проблемы при создании поля большего sizeof(int) но ещё допустимого для size_t Но мы ведь не будем так делать?
    **/
    inline point2i getFieldCoordinatsFromFigureAddress(int address);

    /**
    \brief Возвращает тип фигуры по двумерным координатам
    \param[in] address двумерные (игровые) координаты
    \param[in] offset возможное смещение (для опроса соседей)
    \return тип фигурки, в случаи выхода за границу дапозона FigureType::maxFigure
    \warning Происходит преобразование двумерных координат + смещение в одномерные, и только после проверка. Возможны проблемы что и в getFigureAddressFromFieldCoordinats
    **/
    FigureType getFiureType(point2i address, point2i offset = {0, 0});
protected:
    GameConfig& gameConfig; ///< Ссылка на класс-хранилище конфига
public:
    /**
    \brief Конструктор поля. Запрашивает размеры экрана вычисляя смещения координат для каждой фигурки
    **/
    GameField();
    /**
    \brief Деструктор.
    **/
    ~GameField() override;
    /**
    \brief Инициализатор. Вызывается после конструктора движком.
    **/
    bool init() override;
};
///@}

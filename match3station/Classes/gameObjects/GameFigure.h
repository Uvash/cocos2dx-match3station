/**
	\addtogroup match3station
*/
///@{
#pragma once

#include "cocos2d.h"
#include <functional>
#include "ui/UIWidget.h"
#include "HelpStructures.h"

enum class FigureType	///< Перечисление возможных типов фигурок
{
	CMO,
	CE,
	HOS,
	maxFigure
};

enum class FigureStatus	///< Перечисление возможных статусов фигурок
{
	normal,
	choosen,
	deleted,
	moving,
	maxStatus
};

class GameMode;
/**
	\brief Класс GameFigure. Представляет собой обёртку над спрайтом. Связан с GameField
**/
class GameFigure : public cocos2d::ui::Widget
{
public:
	/**
	\brief Передаёт спрайт в движок для отрисовки
	**/
	Node* getVirtualRenderer() override;

	/**
	\brief Вспомогательный метод для движка для копирования особых переменных
	**/
	void copySpecialProperties(Widget* model) override;

	/**
	\brief Вспомогательный метод для движка для создания коллизии
	**/
	const cocos2d::Size& getContentSize() const override;

	/**
	\brief Устанавливает спрайт по заданным координатам.
	\param[in] pos координаты экрана 
	**/
	void setScreenPosition(const cocos2d::Vec2& pos);

	/**
	\brief Передвигает спрайт в заданные координаты
	\param[in] targetPosition координаты экрана в который движеться спрайт
	**/
	void moveToScreenPosition(cocos2d::Vec2 targetPosition);

	/**
	\brief Возвращает двумерные (игровые) координаты
	\return игровые координаты фигурки
	\warning синхронизируйте с координатами в gameField
	**/
	const point2i& getCoordinats();

	/**
	\brief Устанавливает двумерные (игровые) координаты
	\param[in] target новые координаты фигурки
	\warning синхронизируйте с координатами в gameField
	**/
	void setCoordinats(const point2i& target);	///< Устанавливает двумерные координаты поля

	/**
	\brief Устанавливает тип фигурки. Заменяет и спрайт
	\param[in] type новый тип фигурки
	**/
	void setFigureType(FigureType type);

	/**
	\brief Устанавливает статус фигурки
	\param[in] gStatus Новый статус фигурки
	**/
	void setFigureStatus(FigureStatus gStatus);

	/**
	\brief Возвращает тип фигурки
	\return тип фигурки
	**/
	inline FigureType getFigureType() { return gameType; }

	/**
	\brief Возвращает тип статус
	\return статус фигурки
	**/
	inline FigureStatus getFigureStatus() { return gameStatus;  }
protected:
	FigureStatus gameStatus = FigureStatus::normal;		///< Статус по умолчанию у вновь создаваемых фигур
	FigureType gameType = FigureType::CMO;				///< Тип фигуры по умолчанию у вновь создаваемых фигур
	cocos2d::Sprite* sprite = nullptr;					///< Спрайт по умолчанию у вновь создаваемых фигур
	point2i coordinats = { 0, 0 };						///< Координаты по умолчанию у вновь создаваемых фигур
	GameMode& gameMode;									///< Ссылка на управляющий класс игрового режима
public:
	static GameFigure* create(GameMode& mode);			///< Основной конструктор

	/**
	\brief Инициализатор. Вызывается после конструктора движком.
	**/
	bool init() override;
	/**
	\brief Подключает спрайт к фигуре
	**/
	void initRenderer() override;

	GameFigure() = delete;	///< Удаляем конструктор по умолчанию

	/**
	\brief Конструктор копирования
	\param[in] mode ссылка на оригинал
	**/
	GameFigure(GameMode & mode);

	/**
	\brief Деструктор
	**/
	~GameFigure() override;
public:
	/**
	\brief Вызывается при изменении статуса на FigureStatus::choosen
	**/
	void setChoosen();

	/**
	\brief Вызывается при изменении статуса на FigureStatus::normal
	**/
	void setNormal();

	/**
	\brief Вызывается при изменении статуса на FigureStatus::deleted
	**/
	void setDeleted();

	/**
	\brief Вызывается при изменении статуса на FigureStatus::moving
	**/
	void setMoving();
};
///@}
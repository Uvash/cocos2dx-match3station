/**
	\addtogroup match3station
	\brief Класс фигура. Представляет собой обёртку над спрайтом. Связан с GameField
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
class GameFigure : public cocos2d::ui::Widget
{
public:
	Node* getVirtualRenderer() override;					///< Необходим для корректной работы виджита. 
	void copySpecialProperties(Widget* model) override;		///< Необходим для корректной работы виджита. Копирует настройки.
	const cocos2d::Size& getContentSize() const override;	///< Необходим для корректной работы виджита. Передаёт размер во внутрь движка.

	void setScreenPosition(const cocos2d::Vec2& pos);								///< Устанавливает спрайт в заданных координатах экрана
	void moveToScreenPosition(cocos2d::Vec2 targetPosition);						///< Передвигает спрайт в нужную позицию

	const point2i& getCoordinats();				///< Возвращает двумерные координаты поля
	void setCoordinats(const point2i& target);	///< Устанавливает двумерные координаты поля

	void setFigureType(FigureType type);								///< Устанавливает тип фигуры
	void setFigureStatus(FigureStatus gStatus);							///< Устанавливает статус фигуры
	inline FigureType getFigureType() { return gameType; }				///< Возвращает тип фигуры
	inline FigureStatus getFigureStatus() { return gameStatus;  }		///< Возвращает статус фигуры
protected:
	FigureStatus gameStatus = FigureStatus::normal;		///< Статус по умолчанию у вновь создаваемых фигур
	FigureType gameType = FigureType::CMO;				///< Тип фигуры по умолчанию у вновь создаваемых фигур
	cocos2d::Sprite* sprite = nullptr;					///< Спрайт по умолчанию у вновь создаваемых фигур
	point2i coordinats = { 0, 0 };						///< Координаты по умолчанию у вновь создаваемых фигур
	GameMode& gameMode;									///< Ссылка на управляющий класс игрового режима
public:
	static GameFigure* create(GameMode& mode);			///< Основной конструктор

	bool init() override;								///< Инициализирует фигурку до конца
	void initRenderer() override;						///< Подключает спрайт к фигуре

	GameFigure() = delete;								///< Удаляем конструктор по умолчанию
	GameFigure(GameMode & mode);						///< Конструктор копирования
	~GameFigure() override;								///< Деструктор
public:
	void setChoosen();	///< Устанавливает статус Выбрано
	void setNormal();	///< Устанавливает статус Нормально
	void setDeleted();	///< Устанавливает статус Удалено
	void setMoving();
};
///@}
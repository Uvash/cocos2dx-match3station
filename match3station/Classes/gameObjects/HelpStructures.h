#pragma once
#include <algorithm>

struct point2i
{
	union { int x, w; };
	union { int y, h; };

	inline bool operator== (point2i const& target) const
	{
		if (x == target.x && y == target.y)
			return true;
		return false;
	}

	inline bool operator!= (point2i const& target) 
	{
		if (x == target.x && y == target.y)
			return false;
		return true;
	}

	point2i operator+(const point2i& left)
	{
		return point2i{ x + left.x, y + left.y };
	}

	point2i operator-(const point2i& left)
	{
		return point2i{ x - left.x, y - left.y };
	}

	bool operator<(const point2i& left) const
	{
		if ( operator==(left) )
			return false;

		int normaA = x * x + y * y;
		int normaB = left.x * left.x + left.y * left.y;
		if (normaA == normaB)
		{
			return x < left.x;
		}

		return normaA < normaB;
	}
};
/**
* структура gameScore - хранит "состояние" станции и количество очков
**/

struct gameScore
{
	float hullCondition = 100.0f;
	float crewHealth = 100.0f;
	float order = 100.0f;
	int score = 0;

	inline void setHullCondition(float newValue) { hullCondition = std::clamp(newValue, 0.0f, 100.0f); }
	inline void setCrewHealth(float newValue) { crewHealth = std::clamp(newValue, 0.0f, 100.0f); }
	inline void setOrder(float newValue) { order = std::clamp(newValue, 0.0f, 100.0f); }

	inline void addHullCondition(float newValue) { hullCondition = std::clamp(newValue + hullCondition, 0.0f, 100.0f); }
	inline void addCrewHealth(float newValue) { crewHealth = std::clamp(newValue + crewHealth, 0.0f, 100.0f); }
	inline void addOrder(float newValue) { order = std::clamp(newValue + order, 0.0f, 100.0f); }

};

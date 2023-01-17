#pragma once

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

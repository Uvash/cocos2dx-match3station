#pragma once

struct point2i
{
	union { int x, w; };
	union { int y, h; };

	inline bool operator== (point2i const& target)
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
};


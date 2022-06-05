#pragma once
#include "Structs.h"

namespace utils
{
	inline float DistanceSquared(const glm::vec2& p1, const glm::vec2& p2)
	{
		return powf(p2.x - p1.x, 2.f) + powf(p2.y - p1.y, 2.f);
	}
	inline float Distance(const glm::vec2& p1, const glm::vec2& p2)
	{
		return sqrtf(DistanceSquared(p1, p2));
	}

	inline bool IsOverlapping(const Rectf& r1, const Rectf& r2)
	{
		// If one rectangle is on left side of the other
		if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
		{
			return false;
		}

		// If one rectangle is under the other
		if (r1.top > (r2.top + r2.height) || r2.top > (r1.top + r1.height))
		{
			return false;
		}

		return true;
	}

	inline bool IsPointInRect(const Point2f& p, const Rectf& r)
	{
		return (p.x >= r.left &&
			p.x <= r.left + r.width &&
			p.y >= r.top &&
			p.y <= r.top + r.height);
	}

}

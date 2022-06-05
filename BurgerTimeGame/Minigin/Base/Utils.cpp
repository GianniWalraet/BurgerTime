#include "MiniginPCH.h"
#include "Utils.h"

bool utils::IsOverlapping(const Rectf& r1, const Rectf& r2)
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

bool utils::IsPointInRect(const Point2f& p, const Rectf& r)
{
	return (p.x >= r.left &&
		p.x <= r.left + r.width &&
		p.y >= r.top &&
		p.y <= r.top + r.height);
}

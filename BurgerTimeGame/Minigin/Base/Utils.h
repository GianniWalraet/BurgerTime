#pragma once
#include "Structs.h"

namespace utils
{
	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	bool IsPointInRect(const Point2f& p, const Rectf& r);
}

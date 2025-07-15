#include "stdafx.h"

namespace ratchet
{
	void calculateNormalised(const float& x, const float& y, float& xNorm, float& yNorm)
	{
		const auto length = std::sqrt(x * x + y * y);
		if (length != 0.0f)
		{
			xNorm = x / length;
			yNorm = y / length;
		}
		else
		{
			xNorm = x;
			yNorm = y;
		}
	}
}
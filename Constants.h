#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <algorithm>

#include "Canvas.h"

namespace RTC 
{
	const double epsilon				= std::numeric_limits<double>::epsilon();
	const double positiveInfinity	= std::numeric_limits<double>::infinity();
	const double negativeInfinity	= -1.0f*std::numeric_limits<double>::infinity();
	const double PI = std::atan(1) * 4;

	const double 	kEpsilon = 0.00001;

	const Color Black(0.0, 0.0, 0.0);
	const Color White(1.0, 1.0, 1.0);

	inline bool essentially_equal(double a, double b, double eps = epsilon)
	{
		return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}

	inline bool absoluteToleranceCompare(double x, double y)
	{
		return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
	}

	inline bool floatCompareSpecified(double x, double y, double eps)
	{
		return std::fabs(x - y) <= eps;
	}
}



#endif

#include "Tuple.h"

#include <cmath>

namespace RTC
{
	Tuple::Tuple()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{};

	Tuple::Tuple(double x_, double y_, double z_, double w_)
		:x(x_), y(y_), z(z_), w(w_)
	{}

	Tuple::Tuple(const Tuple& t)
		: x(t.x), y(t.y), z(t.z), w(t.w)
	{}

	Tuple create_tuple_vector(double x_, double y_, double z_)
	{
		return Tuple(x_,y_,z_,0.0f);
	}

	Tuple create_tuple_point(double x_, double y_, double z_)
	{
		return Tuple(x_, y_, z_, 1.0f);
	}

	Tuple operator*(const Tuple& a, double c)
	{
		Tuple ret(a.x, a.y, a.z, a.w);

		ret.x *= c;
		ret.y *= c;
		ret.z *= c;
		ret.w *= c;

		return ret;
	}

	Tuple operator*(double constant, const Tuple& a)
	{
		Tuple ret(a.x, a.y, a.z, a.w);

		ret = a*constant;

		return ret;
	}

	Tuple operator/(const Tuple& a, double c)
	{
		Tuple ret(a.x, a.y, a.z, a.w);

		ret.x /= c;
		ret.y /= c;
		ret.z /= c;
		ret.w /= c;

		return ret;
	}

	double vector_magnitude(const Tuple& a)
	{
		double mag = 0.0f;

		mag = a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w;

		return std::sqrtf(mag);
	}

	Tuple normalize_vector(const Tuple& a)
	{
		double mag = vector_magnitude(a);
		return Tuple(a.x/mag,a.y/mag,a.z/mag,a.w/mag);
	}

	double vector_dot_product(const Tuple& a, const Tuple& b)
	{
		double res = 0.0f;

		res = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

		return res;
	}

	Tuple vector_cross_product(const Tuple& a, const Tuple& b)
	{
		Tuple ret = create_tuple_vector(a.y*b.z - a.z*b.y,
										a.z*b.x - a.x*b.z,
										a.x*b.y - a.y*b.x);

		return ret;
	}

	Tuple operator+(const Tuple& a, const Tuple& b)
	{
		return Tuple(a.x + b.x, a.y+b.y, a.z + b.z, a.w + b.w);
	}

	Tuple operator-(const Tuple& a, const Tuple& b)
	{
		return Tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

}
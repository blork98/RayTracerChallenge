#ifndef TUPLE_H_
#define TUPLE_H_

namespace RTC
{
	struct Tuple
	{
		Tuple();
		Tuple(double x_, double y_, double z_, double w_);
		Tuple(const Tuple& t);
		double x, y, z, w;
	};

	//Create Functions
	Tuple create_tuple_vector(double x_, double y_, double z_);
	Tuple create_tuple_point(double x_, double y_, double z_);

	//Operations
	Tuple operator*(const Tuple& a, double constant);
	Tuple operator*(double constant, const Tuple& a);
	Tuple operator/(const Tuple& a, double constant);
	Tuple operator+(const Tuple& a, const Tuple& b);
	Tuple operator-(const Tuple& a, const Tuple& b);
	
	double vector_magnitude(const Tuple& a);
	double vector_dot_product(const Tuple& a, const Tuple& b);

	Tuple normalize_vector(const Tuple& a);
	Tuple vector_cross_product(const Tuple& a, const Tuple& b);
}
#endif
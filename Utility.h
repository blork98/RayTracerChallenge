#ifndef UTILITY_H_
#define UTILITY_H_

#include <memory>
#include "GeometricObject.h"

namespace RTC
{
	struct Tuple;
	struct Intersection;
	struct ShadeInfo;
	class Ray;
	class GeometricObject;

	//Helper Calculations
	Tuple reflect(const Tuple& in, const Tuple& normal);
	double schlick(ShadeInfo& s);
	
	//Pre Computations
	void prepare_computations(const Ray& ray, const Intersection& intersection, ShadeInfo& s);

	//Helper to create objects
	std::shared_ptr<GeometricObject> create_glass_sphere();

	//Comparison if Intersection
	bool operator==(const Intersection& lhs, const Intersection& rhs);
	bool intersection_compare(const Intersection& lhs, const Intersection& rhs);
	bool compare_intersection(const Intersection& lhs, const Intersection& rhs);
}

#endif
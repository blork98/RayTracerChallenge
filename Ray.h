#ifndef RAY_H_
#define RAY_H_

#include "Tuple.h"
#include <memory>

namespace RTC
{
	class Transform;

	class Ray
	{
	public:
		Ray();
		Ray(Tuple origin, Tuple direction);
		Ray(const Ray& ray);

		Tuple get_direction() const;
		Tuple get_origin() const;
		Tuple position(double t)const;

		void normalize_direction();

	private:
		Tuple origin, direction;
	};

	Ray transform_ray(const Ray& ray, const std::shared_ptr<Transform> transform);
	Ray inverse_transform_ray(const Ray& ray, const std::shared_ptr<Transform> transform);
}

#endif
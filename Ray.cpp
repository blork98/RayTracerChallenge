#include "Ray.h"
#include "Transform.h"
#include "Tuple.h"

namespace RTC
{
	Ray::Ray()
		:origin(create_tuple_point(0.0f,0.0f,0.0f)),
		direction(create_tuple_vector(0.0f,0.0f,0.0f))
	{}

	Ray::Ray(Tuple origin_, Tuple direction_)
		:origin(origin_), direction(direction_)
	{}

	Ray::Ray(const Ray& ray)
		: origin(ray.origin), direction(ray.direction)
	{}

	void Ray::normalize_direction()
	{
		direction = normalize_vector(direction);
	}

	Tuple Ray::get_direction() const
	{
		return direction;
	}

	Tuple Ray::get_origin() const
	{
		return origin;
	}

	Tuple Ray::position(double t)const
	{
		Tuple result = origin + t*direction;

		return result;
	}

	Ray transform_ray(const Ray& ray, const std::shared_ptr<Transform> transform)
	{
		Tuple direction = transform->apply_transform(ray.get_direction());
		Tuple origin = transform->apply_transform(ray.get_origin());

		return Ray(origin, direction);
	}

	Ray inverse_transform_ray(const Ray& ray, const std::shared_ptr<Transform> transform)
	{
		Tuple direction = transform->apply_inverse_transform(ray.get_direction());
		Tuple origin = transform->apply_inverse_transform(ray.get_origin());

		return Ray(origin, direction);
	}

}
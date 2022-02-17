#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <memory>

#include "GeometricObject.h"

namespace RTC
{
	class Light;
	class GeometricObject;
	class Ray;
	class ShadeInfo;
	class Color;

	struct World
	{
	public:
		World();
		World(std::vector<std::shared_ptr<Light>>& lights, std::vector<std::shared_ptr<GeometricObject>>& objects);

		std::vector<std::shared_ptr<Light>> lights;
		std::vector<std::shared_ptr<GeometricObject>> objects;

		std::vector<Intersection> intersect_world(const Ray& ray, ShadeInfo& s);
		Color color_at(const Ray& ray, int remaining);
		bool is_shadowed(Tuple p, std::shared_ptr<Light> light);

		int num_reflect_recurions;
	};

	void create_default_world(World& world);
}

#endif
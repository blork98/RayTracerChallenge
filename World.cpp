#include "World.h"

#include "Light.h"
#include "GeometricObject.h"
#include "Material.h"
#include "Transform.h"
#include "Constants.h"
#include "Utility.h"

namespace RTC
{

	World::World()
		:num_reflect_recurions(1)
	{};

	World::World(std::vector<std::shared_ptr<Light>>& lights_, std::vector<std::shared_ptr<GeometricObject>>& objects_)
		:lights(lights_), objects(objects_), num_reflect_recurions(1)
	{};

	std::vector<Intersection> World::intersect_world(const Ray& ray, ShadeInfo& s)
	{
		std::list<Intersection> intersections;

		bool hit = false;
		double t = positiveInfinity;
		Intersection intersection;

		for (auto object : objects)
		{
			hit = object->hit(ray, t, s);

			if (hit)
			{

				//if (s.hit_t.first >= 0.0)
				//{
				intersection.t = s.hit_t.first;
				intersection.point = s.hit_points.first;
				intersection.object = s.object;
				intersections.push_back(intersection);
				//}

				//if (s.hit_t.second >= 0.0)
				//{
				if (s.num_hits == 2)
				{
					intersection.t = s.hit_t.second;
					intersection.point = s.hit_points.second;
					intersection.object = s.object;
					intersections.push_back(intersection);
				}
				//}

			}
		}

		intersections.sort(compare_intersection);

		return std::move(std::vector<Intersection>(intersections.begin(),intersections.end()));
	}

	Color World::color_at(const Ray& ray, int remaining)
	{
		Color result(0.0f, 0.0f, 0.0f);
		ShadeInfo s;

		std::vector<Intersection> intersections = intersect_world(ray, s);

		//Find first non-negative intersection
		Intersection intersection;
		bool hit = nearest_hit(intersections, intersection);
		//for (auto inter : intersections)
		//{
		//	if (inter.t > 0.0f)
		//	{
		//		intersection = inter;
		//		break;
		//	}
		//}

		if (hit)
		{
			s.intersections = intersections;
			prepare_computations(ray, intersection, s);
			result = s.object->get_material()->shade_hit(*this, s,remaining);
		}

		return result;
	}

	bool World::is_shadowed(Tuple p, std::shared_ptr<Light> light)
	{
		Tuple v = light->get_position() - p;
		double distance = vector_magnitude(v);
		Tuple direction = normalize_vector(v);

		Ray ray(p, direction);
		ShadeInfo s;
		std::vector<Intersection> intersections = intersect_world(ray, s);

		Intersection inter;
		//if( intersections.size() > 0)
		//	hit = intersections[0];
		bool hit = nearest_hit(intersections, inter);

		//if (intersections.size() > 0 && hit.t < distance)
		if( hit && (inter.t < distance))
			return true;
		else
			return false;
	}

	void create_default_world(World& world)
	{
		//Create Light
		if (world.lights.size() != 1)
			world.lights.resize(1);

		std::shared_ptr<Light> light1 = std::make_shared<PointLight>(create_tuple_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
		world.lights[0] = light1;

		//Create Spheres
		if (world.objects.size() != 2)
			world.objects.resize(2);

		//Sphere1
		std::shared_ptr<Phong> material1 = std::make_shared<Phong>();
		material1->set_color(Color(0.8f,1.0f,0.6f));
		material1->set_diffuse(0.7f);
		material1->set_specular(0.2);

		std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		sphere1->set_material(material1);
		world.objects[0] = sphere1;

		//Sphere2
		std::shared_ptr<Transform> transform2 = std::make_shared<Scaling>(0.5f, 0.5f, 0.5f);

		std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		sphere2->set_transform(transform2);
		world.objects[1] = sphere2;

	}

}
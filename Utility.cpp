#include "Utility.h"
#include "Tuple.h"
#include "Constants.h"
#include "Material.h"

#include <algorithm>
#include <cmath>

namespace RTC
{
	Tuple reflect(const Tuple& in, const Tuple& normal)
	{
		return in - normal*2.0f*vector_dot_product(in, normal);
	}

	bool compare_intersection(const Intersection& lhs, const Intersection& rhs)
	{
		if (lhs.t < rhs.t)
			return true;
		else
			return false;
	}

	void prepare_computations(const Ray& ray, const Intersection& intersection, ShadeInfo& s)
	{
		//Copy Intersection data
		s.t = intersection.t;
		s.object = intersection.object;

		//Precompute useful values
		s.hit_point = ray.get_origin() + s.t*ray.get_direction();
		s.hit_point = ray.position(s.t);
		s.eyev = -1.0f*ray.get_direction();
		s.normalv = s.object->get_normal(s.hit_point);

		//Check if Ray hits surface on outside or inside

		double eye_dot_normal = vector_dot_product(s.eyev, s.normalv);

		if (eye_dot_normal <= 0.0)
		{
			s.inside = true;
			s.normalv = -1.0*s.normalv;
		}
		else {
			s.inside = false;
		}

		s.reflectv = reflect(ray.get_direction(), s.normalv);
		s.over_point = s.hit_point + s.normalv*kEpsilon;
		s.under_point = s.hit_point - s.normalv*kEpsilon;

		//Compute n1,n2
		std::list<std::shared_ptr<GeometricObject>> containers;
		
		for (auto i : s.intersections)
		{
			if (i == intersection)
			{
				if (containers.empty())
					s.n1 = 1.0;
				else
					s.n1 = containers.back()->get_material()->get_refractive_index();
			}

			auto x = std::find(containers.begin(), containers.end(), i.object);
			
			if ( x != containers.end())
			{
				containers.erase(x);
			}
			else {
				containers.push_back(i.object);
			}
			
			if (i == intersection)
			{
				if (containers.empty())
					s.n2 = 1.0;
				else
					s.n2 = containers.back()->get_material()->get_refractive_index();

				break;
			}
		}

	}

	bool intersection_compare(const Intersection& lhs, const Intersection& rhs)
	{
		return (lhs.object == rhs.object);
	}

	bool operator==(const Intersection& lhs, const Intersection& rhs)
	{
		return (lhs.object == rhs.object) &&(floatCompareSpecified(lhs.t,rhs.t,0.00001));
	}

	std::shared_ptr<GeometricObject> create_glass_sphere()
	{
		std::shared_ptr<GeometricObject> glass_sphere = std::make_shared<Sphere>();
		
		glass_sphere->get_material()->set_transparency(1.0);
		glass_sphere->get_material()->set_refractive_index(1.5);
		
		return glass_sphere;
	}

	double schlick(ShadeInfo& s)
	{
		double cos = vector_dot_product(s.eyev,s.normalv);

		//TIR if n1>n2
		if (s.n1 > s.n2)
		{
			double n = s.n1 / s.n2;
			double sin2_t = n*n*(1.0 - cos*cos);

			if (sin2_t > 1.0)
				return 1.0;

			double cos_t = std::sqrt(1.0 - sin2_t);

			cos = cos_t;
		}

		double r0 = ((s.n1 - s.n2) / (s.n1 + s.n2))*((s.n1 - s.n2) / (s.n1 + s.n2));

		return r0 + (1 - r0)*std::pow((1-cos),5);
	}
}
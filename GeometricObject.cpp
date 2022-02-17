#include "GeometricObject.h"
#include "Constants.h"
#include "Transform.h"
#include "Material.h"

namespace RTC
{
	ShadeInfo::ShadeInfo()
	{
		num_hits = 0;
		object = NULL;
	}

	GeometricObject::GeometricObject()
	{
		transform = std::make_shared<Transform>();
		material = std::make_shared<Phong>();
	}

	GeometricObject::GeometricObject(const GeometricObject& object)
		:transform(object.transform), material(object.material)
	{}

	void GeometricObject::set_transform(std::shared_ptr<Transform> transform_)
	{
		transform = transform_;
	}

	std::shared_ptr<Transform> GeometricObject::get_transform() const
	{
		return transform;
	}

	void GeometricObject::set_material(std::shared_ptr<Material> mat)
	{
		material = mat;

		//if(material->get_pattern() != nullptr)
		//	material->get_pattern()->set_transform(transform);
	}

	std::shared_ptr<Material> GeometricObject::get_material() const
	{
		return material;
	}

	GeometricObject::~GeometricObject()
	{}

	Sphere::Sphere()
		:GeometricObject(),r(1.0f), center(create_tuple_point(0.0f,0.0f,0.0f))
	{}

	Sphere::Sphere(Tuple center_, double r_)
		: GeometricObject(), r(r_), center(center_)
	{}

	Sphere::Sphere(const Sphere& sphere)
		: GeometricObject(sphere), r(sphere.r), center(sphere.center)
	{}

	Sphere::~Sphere()
	{}

	bool Sphere::hit(const Ray& ray_, double& tmin, ShadeInfo& s) const
	{
		Ray ray = inverse_transform_ray(ray_, get_transform());
		s.local_ray = ray;

		Tuple sphere_to_ray = ray.get_origin() - center;
		double a = vector_dot_product(ray.get_direction(),ray.get_direction());
		double b = 2.0*vector_dot_product(sphere_to_ray, ray.get_direction());
		double c = vector_dot_product(sphere_to_ray, sphere_to_ray) - r*r;
		double disc = b * b - 4.0 * a * c;
		double t1 = 0.0, t2 = 0.0;

		if (disc < 0.0)
		{
			s.num_hits = 0;
			return false;
		}
		else {
			double e = sqrt(disc);
			double denom = 2.0 * a;
			t1 = (-b - e) / denom;    // smaller root
			t2 = (-b + e) / denom;    // larger root

			s.hit_t.first = t1;
			s.hit_t.second = t2;
			s.hit_points.first = ray.get_origin() + t1 * ray.get_direction();
			s.hit_points.second = ray.get_origin() + t2 * ray.get_direction();

			s.num_hits = 2;
			//if (t1 >= 0.0)
			//	s.num_hits += 1;
			//if (t2 >= 0.0)
			//	s.num_hits += 1;

			s.object = std::make_shared<Sphere>(*this);

			/*
			if (t1 > 0.0)
				s.num_hits += 1;

			if (t2 > 0.0)
				s.num_hits += 1;
			*/

			//if (t1 > kEpsilon) {
			//	tmin = t1;
			//	s.hit_point = ray.get_origin() + t1 * ray.get_direction();
			//	//return (true);
			//}

			//if (t2 > kEpsilon) {				
			//	if (t1 < kEpsilon)
			//	{
			//		s.hit_point = ray.get_origin() + t2 * ray.get_direction();
			//		tmin = t2;
			//	}
				//return (true);
			//}

			return true;
		}

		return false;
	}

	Tuple Sphere::get_normal(const Tuple& point) const
	{
		/*
		Tuple result = (point - this->center);
		result = normalize_vector(result);
		return result;
		*/

		Tuple object_point = get_transform()->apply_inverse_transform(point);
		Tuple object_normal = object_point - this->center;
		Tuple world_normal = get_transform()->apply_inverse_transform_trans(object_normal);
		world_normal.w = 0.0f;

		return normalize_vector(world_normal);
	}

	Plane::Plane()
		:GeometricObject()
	{}

	Plane::Plane(const Plane& plane)
		: GeometricObject(plane)
	{}

	Plane::~Plane()
	{}

	Tuple Plane::get_normal(const Tuple& point) const
	{
		Tuple local_normal = create_tuple_vector(0.0, 1.0, 0.0);
		Tuple world_normal = get_transform()->apply_inverse_transform_trans(local_normal);
		world_normal.w = 0.0;

		return normalize_vector(world_normal);
	}

	bool  Plane::hit(const Ray& ray_, double& t, ShadeInfo& s) const
	{
		Ray ray = inverse_transform_ray(ray_, get_transform());

		if (fabs(ray.get_direction().y) < kEpsilon)
		{
			s.num_hits = 0;
			return false;
		}
		
		s.num_hits = 1;

		s.t = -1.0*ray.get_origin().y / ray.get_direction().y;
		t = s.t;
		s.hit_t.first = s.t;
		s.hit_t.second = s.t;
		s.hit_points.first = ray.get_origin() + s.t * ray.get_direction();
		s.hit_points.second = ray.get_origin() + s.t * ray.get_direction();


		s.object = std::make_shared<Plane>(*this);
		//if (s.t > 0.0)
		//	int a = 0;

		return true;
	}

	bool nearist_hit(const std::list<Intersection>& intersections, Intersection& i)
	{
		bool hit = false;
		i.t = positiveInfinity;
		i.object = NULL;

		for (auto intersection : intersections)
		{
			if (intersection.t > 0)
			{
				if (intersection.t < i.t)
				{
					i.t = intersection.t;
					i.object = intersection.object;
					hit = true;
				}
			}
		}

		return hit;
	}

	bool nearest_hit(const std::vector<Intersection>& intersections, Intersection& i)
	{
		bool hit = false;
		i.t = positiveInfinity;
		i.object = NULL;

		for (auto intersection : intersections)
		{
			if (intersection.t > 0)
			{
				if (intersection.t < i.t)
				{
					i.t = intersection.t;
					i.object = intersection.object;
					hit = true;
				}
			}
		}

		return hit;
	}

	Intersection make_intersection(double t, std::shared_ptr<GeometricObject> object)
	{
		Intersection res;

		res.t = t;
		res.object = object;

		return res;
	}

	bool Intersection::operator==(const Intersection& rhs)
	{
		return (rhs.object == this->object) &&(floatCompareSpecified(this->t,rhs.t,0.00001));
	}

}

#ifndef GEOMETRICOBJECT_H_
#define GEOMETRICOBJECT_H_

#include "Tuple.h"
#include "Ray.h"
#include "Canvas.h"
#include "Light.h"
#include <memory>
#include <list>

namespace RTC
{
	class GeometricObject;
	class Transform;
	class Material;

	struct Intersection
	{
		double t;
		Tuple point;
		std::shared_ptr<GeometricObject> object;

		bool operator==(const Intersection& rhs);
	};
	
	struct ShadeInfo
	{
	public:
		ShadeInfo();

		bool hit_an_object;
		std::pair<double, double> hit_t;
		std::pair<Tuple, Tuple> hit_points;
		int num_hits;    //number of times hit
		Tuple hit_point; //local hit point
		Ray ray;

		//shading
		Tuple normalv;
		Tuple eyev;
		double t;
		bool inside;
		bool in_shadow;
		Tuple over_point;
		Tuple under_point;
		Tuple reflectv;

		//utility styff
		Ray local_ray;
		Tuple local_normal;

		//Refraction
		std::vector<Intersection> intersections;
		double n1, n2;

		std::shared_ptr<GeometricObject> object;
	};

	//Intersection Functions
	Intersection make_intersection(double t, std::shared_ptr<GeometricObject> object);
	bool nearist_hit(const std::list<Intersection>& intersecions, Intersection& i);
	bool nearest_hit(const std::vector<Intersection>& intersecions, Intersection& i);

	class GeometricObject
	{
	public:
		GeometricObject();									
		GeometricObject(const GeometricObject& object);

		virtual ~GeometricObject();

		virtual bool hit(const Ray& ray, double& t, ShadeInfo& s) const = 0;
		virtual Tuple get_normal(const Tuple& point) const = 0;

		void set_transform(std::shared_ptr<Transform> transform);
		std::shared_ptr<Transform> get_transform() const;

		void set_material(std::shared_ptr<Material> material);
		std::shared_ptr<Material> get_material() const;

	private:
		std::shared_ptr<Transform> transform;
		std::shared_ptr<Material> material;
	};

	class Plane : public GeometricObject
	{
	public:
		Plane();
		Plane(const Plane& plane);

		virtual ~Plane();

		virtual bool hit(const Ray& ray, double& t, ShadeInfo& s) const;
		virtual Tuple get_normal(const Tuple& point) const;

	};

	class Sphere : public GeometricObject
	{
	public:
		Sphere();   									
		Sphere(Tuple center, double r);					
		Sphere(const Sphere& sphere); 						

		virtual ~Sphere();	

		virtual bool hit(const Ray& ray, double& t, ShadeInfo& s) const;
		virtual Tuple get_normal(const Tuple& point) const;
		
	private:
		Tuple center;
		double r;
	};
}

#endif

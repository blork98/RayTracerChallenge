#include "Constants.h"
#include "PlaneTests.h"
#include "GeometricObject.h"
#include "Transform.h"

#include <cmath>
#include <iostream>

using namespace RTC;

void plane_tests()
{
	std::cout<<"Plane Tests...." << std::endl;

	test_local_ray();
	test_local_normal();
	test_plane();

	std::cout << std::endl << std::endl;
}

void test_plane()
{
	//Plane normal test
	Plane p;
	Tuple n1 = p.get_normal(create_tuple_point(0.0, 0.0, 0.0));
	Tuple n2 = p.get_normal(create_tuple_point(10.0,0.0,-10.0));
	Tuple n3 = p.get_normal(create_tuple_point(-5.0, 0.0, 150.0));

	bool test1 = essentially_equal(n1.x, 0.0) && essentially_equal(n1.y, 1.0) && essentially_equal(n1.z, 0.0);
	bool test2 = essentially_equal(n2.x, 0.0) && essentially_equal(n2.y, 1.0) && essentially_equal(n2.z, 0.0);
	bool test3 = essentially_equal(n3.x, 0.0) && essentially_equal(n3.y, 1.0) && essentially_equal(n3.z, 0.0);

	if (test1&&test2&&test3)
		std::cout << "The Normal of a Plane is constant: Test Passed" << std::endl;
	else
		std::cout << "The Normal of a Plane is constant: Test Failed" << std::endl;

	//Ray intersect
	double t = 0.0;
	ShadeInfo s;
	Ray r1(create_tuple_point(0.0,10.0,0.0),create_tuple_vector(0.0,0.0,1.0));
	bool hit1 = p.hit(r1, t, s);

	if (!hit1)
		std::cout << "Intersect with a Ray Parallel to Plane: Test Passed" << std::endl;
	else
		std::cout << "Intersect with a Ray Parallel to Plane: Test Failed" << std::endl;

	Ray r2(create_tuple_point(0.0, 0.0, 0.0), create_tuple_vector(0.0, 0.0, 1.0));
	bool hit2 = p.hit(r2, t, s);

	if (!hit2)
		std::cout << "Intersect with a Coplanar Ray: Test Passed" << std::endl;
	else
		std::cout << "Intersect with a Coplanar Ray: Test Failed" << std::endl;
	
	Ray r3(create_tuple_point(0.0, 1.0, 0.0), create_tuple_vector(0.0, -1.0, 0.0));
	bool hit3 = p.hit(r3, t, s);
	test1 = essentially_equal(s.t, 1.0) && (s.num_hits == 1)&(s.object != nullptr);

	if (hit3 && test1)
		std::cout << "Ray Intersecting Plane from above: Test Passed" << std::endl;
	else
		std::cout << "Ray Intersecting Plane from above: Test Failed" << std::endl;

	Ray r4(create_tuple_point(0.0, -1.0, 0.0), create_tuple_vector(0.0, 1.0, 0.0));
	bool hit4 = p.hit(r4, t, s);
	test1 = essentially_equal(s.t, 1.0) && (s.num_hits == 1)&(s.object != nullptr);

	if (hit4 && test1)
		std::cout << "Ray Intersecting Plane from below: Test Passed" << std::endl;
	else
		std::cout << "Ray Intersecting Plane from below: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_local_normal()
{
	Sphere sphere1(create_tuple_point(0.0, 0.0, 0.0), 1.0);
	sphere1.set_transform(std::make_shared<Translation>(0.0, 1.0, 0.0));
	Tuple normal1 = sphere1.get_normal(create_tuple_point(0,1.70711,-0.70711));
	bool test1 = floatCompareSpecified(normal1.x, 0.0, 0.00001) &&
		floatCompareSpecified(normal1.y, 0.70711, 0.00001) &&
		floatCompareSpecified(normal1.z, -0.70711, 0.00001);
	if (test1)
		std::cout << "Computing the Normal on Translated Sphere: Test Passed" << std::endl;
	else
		std::cout << "Computing the Normal on Translated Sphere: Test Failed" << std::endl;
	
	Sphere sphere2(create_tuple_point(0.0, 0.0, 0.0), 1.0);
	std::vector<std::shared_ptr<Transform>> transforms(2);
	std::shared_ptr<Rotation> rot1 = std::make_shared<Rotation>();
	rot1->rotate_z(M_PI / 5.0);
	transforms[0] = rot1;
	transforms[1] = std::make_shared<Scaling>(1.0,0.5,1.0);
	sphere2.set_transform(std::make_shared<CompoundTransform>(transforms));
	Tuple normal2 = sphere2.get_normal(create_tuple_point(0, 0.5*std::sqrt(2.0), -0.5*std::sqrt(2.0)));
	bool test2 = floatCompareSpecified(normal2.x, 0.0, 0.00001) &&
		floatCompareSpecified(normal2.y, 0.97014, 0.00001) &&
		floatCompareSpecified(normal2.z, -0.24254, 0.00001);
	if (test2)
		std::cout << "Computing the Normal on Transformed Sphere: Test Passed" << std::endl;
	else
		std::cout << "Computing the Normal on Transformed Sphere: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_local_ray()
{
	Ray ray1(create_tuple_point(0.0,0.0,-5.0),create_tuple_vector(0.0,0.0,1.0));
	Sphere sphere1(create_tuple_point(0.0,0.0,0.0),1.0);
	sphere1.set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));

	ShadeInfo s;
	double t = 0.0;
	bool test1 = sphere1.hit(ray1, t, s);
	bool test1o = essentially_equal(0.0f, s.local_ray.get_origin().x) &&
		essentially_equal(0.0f, s.local_ray.get_origin().y) &&
		essentially_equal(-2.5f, s.local_ray.get_origin().z);
	bool test1d = essentially_equal(0.0f, s.local_ray.get_direction().x) &&
		essentially_equal(0.0f, s.local_ray.get_direction().y) &&
		essentially_equal(0.5f, s.local_ray.get_direction().z);

	if (test1o && test1d)
		std::cout << "Intersecting Scaled Shape with Ray: Test Passed" << std::endl;
	else
		std::cout << "Intersecting Scaled Shape with Ray: Test Failed" << std::endl;

	Ray ray2(create_tuple_point(0.0, 0.0, -5.0), create_tuple_vector(0.0, 0.0, 1.0));
	Sphere sphere2(create_tuple_point(0.0, 0.0, 0.0), 1.0);
	sphere2.set_transform(std::make_shared<Translation>(5.0, 0.0, 0.0));

	bool test2 = sphere2.hit(ray2, t, s);
	bool test2o = essentially_equal(-5.0f, s.local_ray.get_origin().x) &&
		essentially_equal(0.0f, s.local_ray.get_origin().y) &&
		essentially_equal(-5.0f, s.local_ray.get_origin().z);
	bool test2d = essentially_equal(0.0f, s.local_ray.get_direction().x) &&
		essentially_equal(0.0f, s.local_ray.get_direction().y) &&
		essentially_equal(1.0f, s.local_ray.get_direction().z);

	if (test2o && test2d)
		std::cout << "Intersecting Translated Shape with Ray: Test Passed" << std::endl;
	else
		std::cout << "Intersecting Translated Shape with Ray: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}
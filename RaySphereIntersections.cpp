#include "Constants.h"
#include "RaySphereIntersection.h"
#include "Ray.h"
#include "GeometricObject.h"
#include "Transform.h"
#include <iostream>
#include <list>

using namespace RTC;

void ray_sphere_intersection_tests()
{
	std::cout << "Ray Sphere Intersection Tests:" << std::endl << std::endl;

	test_ray();
	test_intersection();
	test_ray_object_transforms();

	std::cout << std::endl << std::endl;
}

void test_ray_object_transforms()
{
	std::cout << "Ray and Object Transforms Tests:" << std::endl;
	
	//Translation
	Ray ray(create_tuple_point(1.0f,2.0f,3.0f),create_tuple_vector(0.0f,1.0f,0.0f));
	std::shared_ptr<Transform> transform1 = std::make_shared<Translation>(3.0f,4.0f,5.0f);
	Ray rayTrans = transform_ray(ray,transform1);

	bool test1 = essentially_equal(4.0f, rayTrans.get_origin().x)&& essentially_equal(6.0f, rayTrans.get_origin().y)&& essentially_equal(8.0f, rayTrans.get_origin().z);
	bool test2 = essentially_equal(0.0f, rayTrans.get_direction().x) && essentially_equal(1.0f, rayTrans.get_direction().y) && essentially_equal(0.0f, rayTrans.get_direction().z);

	if (test1&&test2)
		std::cout << "Translate Ray : Test Passed" << std::endl;
	else
		std::cout << "Translate Ray : Test Failed" << std::endl;

	//Scaling
	std::shared_ptr<Transform> transform2 = std::make_shared<Scaling>(2.0f, 3.0f, 4.0f);
	rayTrans = transform_ray(ray, transform2);

	test1 = essentially_equal(2.0f, rayTrans.get_origin().x) && essentially_equal(6.0f, rayTrans.get_origin().y) && essentially_equal(12.0f, rayTrans.get_origin().z);
	test2 = essentially_equal(0.0f, rayTrans.get_direction().x) && essentially_equal(3.0f, rayTrans.get_direction().y) && essentially_equal(0.0f, rayTrans.get_direction().z);

	if (test1&&test2)
		std::cout << "Translate Ray : Test Passed" << std::endl;
	else
		std::cout << "Translate Ray : Test Failed" << std::endl;

	//Test Sphere
	Sphere sphere;
	std::cout << "Default Transform for Sphere is Identity: Test Passed" << std::endl;
	
	sphere.set_transform(std::make_shared<Translation>(2.0f, 3.0f, 4.0f));
	std::cout << "Set Transform for Sphere: Test Passed" << std::endl;

	//Test Scaled Sphere Intersection
	Ray ray1(create_tuple_point(0.0f, 0.0f, -5.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	Sphere sphere1(create_tuple_point(0.0f,0.0f,0.0f),1.0f);
	sphere1.set_transform(std::make_shared<Scaling>(2.0f, 2.0f, 2.0f));
	
	ShadeInfo s;
	double t;

	bool hitTest = sphere1.hit(ray1, t, s);
	test1 = s.num_hits == 2;
	test2 = essentially_equal(s.hit_t.first, 3.0f) && essentially_equal(s.hit_t.second, 7.0f);

	if (test1&&test2&&hitTest)
		std::cout << "Scaled Sphere Intersection with Ray : Test Passed" << std::endl;
	else
		std::cout << "Scaled Sphere Intersection with Ray : Test Failed" << std::endl;

	//Test Translated Sphere Intersection
	sphere1.set_transform(std::make_shared<Translation>(5.0f, 0.0f, 0.0f));

	hitTest = sphere1.hit(ray1, t, s);
	test1 = s.num_hits == 0;

	if (test1&&!hitTest)
		std::cout << "Translated Sphere Intersection with Ray : Test Passed" << std::endl;
	else
		std::cout << "Translated Sphere Intersection with Ray : Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_intersection()
{
	std::cout << "Sphere Intersection Tests:" << std::endl;

	Ray ray(create_tuple_point(0.0f,0.0f,-5.0f), create_tuple_vector(0.0f,0.0f,1.0f));
	Sphere sphere1(create_tuple_point(0.0f,0.0f,0.0f),1.0f);

	ShadeInfo s;
	double t;

	bool hitTest1 = sphere1.hit(ray, t, s);
	bool hitTest2 = s.num_hits == 2;
	bool hitTest3 = essentially_equal(s.hit_t.first, 4.0) && essentially_equal(s.hit_t.second,6.0);

	if( hitTest1 && hitTest2&&hitTest3)
		std::cout << " Test Sphere Intersection 2 points: Test Passed" << std::endl;
	else
		std::cout << " Test Sphere Intersection 2 points: Test Failed" << std::endl;

	Ray ray2(create_tuple_point(0.0f, 1.0f, -5.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	hitTest1 = sphere1.hit(ray2, t, s);
	hitTest2 = s.num_hits == 2;
	hitTest3 = essentially_equal(s.hit_t.first, 5.0) && essentially_equal(s.hit_t.second, 5.0);

	if (hitTest1 && hitTest2&&hitTest3)
		std::cout << " Test Sphere Intersection Tangent: Test Passed" << std::endl;
	else
		std::cout << " Test Sphere Intersection Tangent: Test Failed" << std::endl;

	Ray ray3(create_tuple_point(0.0f, 2.0f, -5.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	hitTest1 = sphere1.hit(ray3, t, s);
	hitTest2 = s.num_hits == 0;

	if (!hitTest1 && hitTest2)
		std::cout << " Test Sphere Intersection Miss: Test Passed" << std::endl;
	else
		std::cout << " Test Sphere Intersection Miss: Test Failed" << std::endl;

	Ray ray4(create_tuple_point(0.0f, 0.0f, 0.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	hitTest1 = sphere1.hit(ray4, t, s);
	hitTest2 = s.num_hits == 2;
	hitTest3 = essentially_equal(s.hit_t.first, -1.0) && essentially_equal(s.hit_t.second, 1.0);

	

	if (hitTest1 && hitTest2&&hitTest3)
		std::cout << " Test Sphere Intersection Inside Sphere: Test Passed" << std::endl;
	else
		std::cout << " Test Sphere Intersection Inside Sphere: Test Failed" << std::endl;

	Ray ray5(create_tuple_point(0.0f, 0.0f, 5.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	hitTest1 = sphere1.hit(ray5, t, s);
	hitTest2 = s.num_hits == 2;
	hitTest3 = essentially_equal(s.hit_t.first, -6.0) && essentially_equal(s.hit_t.second, -4.0);

	if (hitTest1 && hitTest2&&hitTest3)
		std::cout << " Test Sphere Intersection In Front of Sphere: Test Passed" << std::endl;
	else
		std::cout << " Test Sphere Intersection In Front of Sphere: Test Failed" << std::endl;

	std::list<Intersection> intersections;
	Intersection i1;
	i1.t =1.0;
	i1.object = s.object;
	intersections.push_back(i1);

	Intersection i2;
	i2.t = 2.0;
	i2.object = s.object;
	intersections.push_back(i2);

	

	std::cout << "Test Intersection Aggregation: " << std::endl;
	for (auto inter : intersections)
		std::cout<<" T: " << inter.t << " Object Address:    " << &(inter.object) << std::endl;

	//Test Intersection Closest Hit

	std::vector<Intersection> intersectionList;
	Intersection res, i3, i4;
	i1.t = 5.0;
	i1.object = s.object;
	i2.t = 7.0;
	i2.object = s.object;
	i3.t = -3.0;
	i3.object = s.object;
	i4.t = 2.0;
	i4.object = s.object;

	intersectionList.push_back(i1);
	intersectionList.push_back(i2);
	intersectionList.push_back(i3);
	intersectionList.push_back(i4);

	bool test1 = nearest_hit(intersectionList, res);
	bool test2 = essentially_equal(2.0f, res.t);

	if (test2)
		std::cout << "Test Intersection Aggregation Nearest Hit: Test Passed" << std::endl;
	else
		std::cout << "Test Intersection Aggregation Nearest Hit: Test Failed" << std::endl;

	std::vector<Intersection> intersection;
	i1.t = -2.0;
	i1.object = s.object;
	i2.t = -1.0;
	i2.object = s.object;
	test1 = nearest_hit(intersection, res);

	std::cout << std::endl;
}

void test_ray()
{
	std::cout << "Ray Tests:" << std::endl;
	Tuple origin = create_tuple_point(2.0f, 3.0f, 4.0f);
	Tuple direction = create_tuple_vector(1.0f, 0.0f, 0.0f);

	Ray r(origin, direction);
	Tuple point1 = r.position(0.0f);
	bool test1 = essentially_equal(2.0f, point1.x) && essentially_equal(3.0f, point1.y) && essentially_equal(4.0f, point1.z);

	if (test1)
		std::cout << " Test Position(r,0): Test Passed" << std::endl;
	else
		std::cout << " Test Position(r,0): Test Failed" << std::endl;

	point1 = r.position(1.0f);
	test1 = essentially_equal(3.0f, point1.x) && essentially_equal(3.0f, point1.y) && essentially_equal(4.0f, point1.z);

	if (test1)
		std::cout << " Test Position(r,1): Test Passed" << std::endl;
	else
		std::cout << " Test Position(r,1): Test Failed" << std::endl;

	point1 = r.position(-1.0f);
	test1 = essentially_equal(1.0f, point1.x) && essentially_equal(3.0f, point1.y) && essentially_equal(4.0f, point1.z);

	if (test1)
		std::cout << " Test Position(r,-1): Test Passed" << std::endl;
	else
		std::cout << " Test Position(r,-1): Test Failed" << std::endl;

	point1 = r.position(2.5f);
	test1 = essentially_equal(4.5f, point1.x) && essentially_equal(3.0f, point1.y) && essentially_equal(4.0f, point1.z);

	if (test1)
		std::cout << " Test Position(r,2.5): Test Passed" << std::endl;
	else
		std::cout << " Test Position(r,2.5): Test Failed" << std::endl;

		
	std::cout << std::endl;
}
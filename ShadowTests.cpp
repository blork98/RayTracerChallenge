#include "ShadowTests.h"
#include "Material.h"
#include "GeometricObject.h"
#include "Canvas.h"
#include "Constants.h"
#include "World.h"
#include "Transform.h"
#include "Utility.h"

#include <iostream>
#include <fstream>

using namespace RTC;

void shadow_tests()
{
	std::cout << "Shadow Tests:" << std::endl << std::endl;

	test_shadows();
	test_over_point();
	test_shade_hit();

	std::cout << std::endl << std::endl;
}

void test_shade_hit()
{
	//Test shade_hit
	World world;
	world.lights = std::vector < std::shared_ptr<Light>>(1);
	world.lights[0] = std::make_shared<PointLight>(create_tuple_point(0.0f,0.0f,-10.0f),Color(1.0f,1.0f,1.0f));

	world.objects = std::vector<std::shared_ptr<GeometricObject>>(2);

	world.objects[0] = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	world.objects[1] = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	world.objects[1]->set_transform(std::make_shared < Translation>(0.0f, 0.0f, 10.0f));

	Ray r(create_tuple_point(0.0f, 0.0f, 5.0f), create_tuple_vector(0.0f, 0.0f, 1.0f));
	ShadeInfo s;
	double t;
	bool hit2 = world.objects[1]->hit(r, t, s);

	Intersection intersection;
	intersection.t = s.hit_t.first;
	intersection.object = s.object;

	prepare_computations(r, intersection, s);
	Color c = world.objects[1]->get_material()->shade_hit(world, s,1);
	bool test = floatCompareSpecified(c.red, 0.1f, 0.00001) && floatCompareSpecified(c.green, 0.1f, 0.00001) && floatCompareSpecified(c.blue, 0.1f,0.00001);

	if (test)
		std::cout << "Test Shade Hit on Intersection: Test Passed" << std::endl;
	else
		std::cout << "Test Shade Hit on Intersection: Test Failed" << std::endl;

	std::cout << std::endl;

}

void test_over_point()
{
	//Test Over point calculation
	Ray r(create_tuple_point(0.0f,0.0f,-5.0f),create_tuple_vector(0.0f,0.0f,1.0f));
	Sphere sphere(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	sphere.set_transform(std::make_shared<Translation>(0.0f,0.0f,1.0f));

	ShadeInfo s;
	double t;
	bool hit = sphere.hit(r, t, s);

	Intersection intersection;
	intersection.t = s.hit_t.first;
	intersection.object = s.object;
	intersection.point = s.hit_points.first;

	prepare_computations(r, intersection, s);

	bool test1 = (s.over_point.z < -0.5*kEpsilon);
	bool test2 = (s.hit_point.z > s.over_point.z);

	if (test1&&test2)
		std::cout << "Over Point Calculation Test: Passed" << std::endl;
	else
		std::cout << "Over Point Calculation Test: Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_shadows()
{
	//Surface in Shadow Lighting

	ShadeInfo s;
	s.in_shadow = true;
	s.eyev = create_tuple_vector(0.0f, 0.0f, -1.0f);
	s.normalv = create_tuple_vector(0.0f, 0.0f, -1.0f);
	
	std::shared_ptr<Light> light = std::make_shared<PointLight>(create_tuple_point(0.0f,0.0f,-10.0f),Color(1.0f,1.0f,1.0f));
	Phong m;

	Color c = m.lighting(light, s);

	bool test = essentially_equal(c.red, 0.1f) && essentially_equal(c.green, 0.1f) && essentially_equal(c.blue, 0.1f);
	if (test)
		std::cout << "Test Lighting with Surface in Shadow: Test Passed" << std::endl;
	else
		std::cout << "Test Lighting with Surface in Shadow: Test Failed" << std::endl;

	//Testing for shadows
	World world;
	create_default_world(world);
	Tuple point = create_tuple_point(0.0f, 10.0f, 0.0f);
	bool test1 = world.is_shadowed(point,world.lights[0]);
	if (!test1)
		std::cout << "There is no shadow when nothing is colinear with point and light: Test Passed" << std::endl;
	else
		std::cout << "There is no shadow when nothing is colinear with point and light: Test Failed" << std::endl;

	point = create_tuple_point(10.0f, -10.0f, 10.0f);
	test1 = world.is_shadowed(point, world.lights[0]);
	if (test1)
		std::cout << "Shadow when object is between point and light: Test Passed" << std::endl;
	else
		std::cout << "Shadow when object is between point and light: Test Failed" << std::endl;

	point = create_tuple_point(-20.0f, 20.0f, -20.0f);
	test1 = world.is_shadowed(point, world.lights[0]);
	if (!test1)
		std::cout << "There is no shadow when object is behind the light: Test Passed" << std::endl;
	else
		std::cout << "There is no shadow when object is behind the light: Test Failed" << std::endl;

	point = create_tuple_point(-2.0f, 2.0f, -2.0f);
	test1 = world.is_shadowed(point, world.lights[0]);
	if (!test1)
		std::cout << "There is no shadow when object is behind the point: Test Passed" << std::endl;
	else
		std::cout << "There is no shadow when object is behind the point: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

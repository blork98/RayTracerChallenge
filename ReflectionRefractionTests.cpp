#include "ReflectionRefractionTests.h"

#include "GeometricObject.h"
#include "Material.h"
#include "Utility.h"
#include "Constants.h"
#include "World.h"
#include "Pattern.h"

#include <iostream>

using namespace RTC;

class TestPattern : public Pattern
{
public:
	Color pattern_at(Tuple point) const
	{
		return Color(point.x, point.y, point.z);
	}
};

void reflection_refraction_tests()
{
	std::cout << "Reflaction and Refraction Tests:" << std::endl << std::endl;

	test_reflection_mat();
	test_reflective_surface_hit();
	test_infinite_recursion();
	test_limit_recursion();
	test_refraction_index();
	test_refracted_color();
	test_refracted_color_f();
	test_refracted_shade_hit();
	test_fresnel();
	test_fresnel_shade_hit();

	std::cout << std::endl << std::endl;
}

void test_fresnel_shade_hit()
{
	World w;
	create_default_world(w);

	Ray ray(create_tuple_point(0.0, 0.0, -3.0), create_tuple_vector(0.0, -0.5*std::sqrt(2.0), 0.5*std::sqrt(2.0)));

	//Create Floor
	std::shared_ptr < GeometricObject > floor = std::make_shared<Plane>();
	floor->set_transform(std::make_shared<Translation>(0.0,-1.0,0.0));
	floor->get_material()->set_reflective(0.5);
	floor->get_material()->set_transparency(0.5);
	floor->get_material()->set_refractive_index(1.5);
	w.objects.push_back(floor);
	
	//Create Ball
	std::shared_ptr < GeometricObject > ball = std::make_shared<Sphere>();
	ball->set_transform(std::make_shared<Translation>(0, -3.5, -0.5));
	std::shared_ptr<Phong> ball_mat = std::make_shared<Phong>();
	ball_mat->set_color(Color(1.0, 0.0, 0.0));
	ball_mat->set_ambient(0.5);
	ball->set_material(ball_mat);
	w.objects.push_back(ball);

	std::vector<Intersection> isects3(1);
	isects3[0].t = std::sqrt(2);
	isects3[0].object = floor;

	ShadeInfo s;
	s.intersections = isects3;

	prepare_computations(ray, isects3[0], s);

	Color c = floor->get_material()->shade_hit(w, s, 5);
	bool test = floatCompareSpecified(c.red, 0.93391, 0.00001) && floatCompareSpecified(c.green, 0.69643, 0.00001) && floatCompareSpecified(c.blue, 0.69243, 0.00001);
	if (test)
		std::cout << "Shade Hit with Reflective and Transparent Material: Test Passed" << std::endl;
	else
		std::cout << "Shade Hit with Reflective and Transparent Material: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_fresnel()
{
	//Fresnel Test 1
	std::shared_ptr<GeometricObject> shape1 = create_glass_sphere();
	Ray r1(create_tuple_point(0.0, 0.0, 0.5*std::sqrt(2.0)), create_tuple_vector(0.0, 1.0, 0.0));
	std::vector<Intersection> isects1(2);
	isects1[0].t = -0.5*std::sqrt(2.0);
	isects1[0].object = shape1;
	isects1[1].t = 0.5*std::sqrt(2.0);
	isects1[1].object = shape1;

	ShadeInfo s;
	s.intersections = isects1;

	prepare_computations(r1, isects1[1], s);
	double res = schlick(s);

	bool test1 = essentially_equal(res, 1.0);
	if (test1)
		std::cout << "Schlick under TIR: Test Passed" << std::endl;
	else
		std::cout << "Schlick under TIR: Test Failed" << std::endl;

	//Test 2
	Ray r2(create_tuple_point(0.0, 0.0, 0.0), create_tuple_vector(0.0, 1.0, 0.0));
	std::vector<Intersection> isects2(2);
	isects2[0].t = -1.0;
	isects2[0].object = shape1;
	isects2[1].t = 1.0;
	isects2[1].object = shape1;

	s.intersections = isects2;
	prepare_computations(r2, isects2[1], s);
	res = schlick(s);
	test1 = essentially_equal(res, 0.04);
	if (test1)
		std::cout << "Schlick approx with Perpendicular angle: Test Passed" << std::endl;
	else
		std::cout << "Schlick approx with Perpendicular angle: Test Failed" << std::endl;

	//Test 3
	Ray r3(create_tuple_point(0.0, 0.99, -2.0), create_tuple_vector(0.0, 0.0, 1.0));
	std::vector<Intersection> isects3(1);
	isects3[0].t = 1.8589;
	isects3[0].object = shape1;

	s.intersections = isects3;
	prepare_computations(r3, isects3[0], s);
	res = schlick(s);
	test1 = floatCompareSpecified(res, 0.48873,0.00001);
	if (test1)
		std::cout << "Schlick approx with small angle and n2 > n1: Test Passed" << std::endl;
	else
		std::cout << "Schlick approx with small angle and n2 > n1: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_refracted_shade_hit()
{
	World w;
	create_default_world(w);

	std::shared_ptr<GeometricObject> floor = std::make_shared<Plane>();
	floor->set_transform(std::make_shared<Translation>(0, -1.0, 0.0));
	floor->get_material()->set_transparency(0.5);
	floor->get_material()->set_refractive_index(1.5);
	w.objects.push_back(floor);

	std::shared_ptr<GeometricObject> ball = std::make_shared<Sphere>();
	std::shared_ptr<Phong> ball_mat = std::make_shared<Phong>();
	ball_mat->set_color(Color(1.0,0.0,0.0));
	ball_mat->set_ambient(0.5);
	ball->set_material(ball_mat);
	ball->set_transform(std::make_shared<Translation>(0, -3.5, -0.5));
	w.objects.push_back(ball);

	Ray ray(create_tuple_point(0.0, 0.0, -3.0), create_tuple_vector(0.0, -0.5*std::sqrt(2.0), 0.5*std::sqrt(2.0)));
	std::vector<Intersection> intersections(1);
	intersections[0].t = std::sqrt(2.0);
	intersections[0].object = floor;

	ShadeInfo s;
	s.intersections = intersections;

	prepare_computations(ray, intersections[0], s);
	Color c = floor->get_material()->shade_hit(w, s, 5);

	bool test = floatCompareSpecified(c.red, 0.93642, 0.00001) && floatCompareSpecified(c.green, 0.68642, 0.00001) && floatCompareSpecified(c.blue, 0.68642, 0.00001);

	if (test)
		std::cout << "Shade Hit with Transparent Material: Test Passed" << std::endl;
	else
		std::cout << "Shade Hit with Transparent Material: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_refracted_color_f()
{
	//refracted color
	World w;
	create_default_world(w);

	std::shared_ptr<Phong> mat_a = std::make_shared<Phong>();
	mat_a->set_ambient(1.0);
	mat_a->set_pattern(std::make_shared<TestPattern>());
	w.objects[0]->set_material(mat_a);

	w.objects[1]->get_material()->set_refractive_index(1.5);
	w.objects[1]->get_material()->set_transparency(1.0);

	Ray r(create_tuple_point(0.0, 0.0, 0.1), create_tuple_vector(0.0, 1.0, 0.0));

	ShadeInfo s;
	s.intersections = std::vector<Intersection>(4);
	s.intersections[0].t = -0.9899;
	s.intersections[0].object = w.objects[0];
	s.intersections[1].t = -0.4899;
	s.intersections[1].object = w.objects[1];
	s.intersections[2].t = 0.4899;
	s.intersections[2].object = w.objects[1];
	s.intersections[3].t = 0.9899;
	s.intersections[3].object = w.objects[0];

	prepare_computations(r, s.intersections[2], s);

	Color c = w.objects[1]->get_material()->refracted_color(w, s, 5);

	bool test = floatCompareSpecified(c.red, 0.0, 0.0001) && floatCompareSpecified(c.green, 0.99888, 0.0001) && floatCompareSpecified(c.blue, 0.04725,0.0001);

	if (test)
		std::cout << "Refracted Color with Refracted Ray: Test Passed" << std::endl;
	else
		std::cout << "Refracted Color with Refracted Ray: Test Failed" << std::endl;


	std::cout << std::endl;
}

void test_refracted_color()
{
	//Refracted Color of Opaque Object
	World w;
	create_default_world(w);

	std::shared_ptr<GeometricObject> shape = w.objects[0];

	Ray ray(create_tuple_point(0.0, 0.0, -5.0), create_tuple_vector(0.0, 0.0, 1.0));

	ShadeInfo s;
	s.intersections = std::vector<Intersection>(2);
	s.intersections[0].t = 4.0;
	s.intersections[0].object = shape;
	s.intersections[1].t = 6.0;
	s.intersections[1].object = shape;

	prepare_computations(ray, s.intersections[0], s);
	Color c = shape->get_material()->refracted_color(w, s, 5);

	bool test = essentially_equal(Black.red, c.red) && essentially_equal(Black.green, c.green) && essentially_equal(Black.blue, c.blue);
	if (test)
		std::cout << "Refracted Color with Opaque Surface: Test Passed" << std::endl;
	else
		std::cout << "Refracted Color with Opaque Surface: Test Failed" << std::endl;

	//Refracted Color at Max Depth
	shape->get_material()->set_refractive_index(1.5);
	shape->get_material()->set_transparency(1.0);
	prepare_computations(ray, s.intersections[0], s);
	c = shape->get_material()->refracted_color(w, s, 0);

	test = essentially_equal(Black.red, c.red) && essentially_equal(Black.green, c.green) && essentially_equal(Black.blue, c.blue);
	if (test)
		std::cout << "Refracted Color at Max Depth: Test Passed" << std::endl;
	else
		std::cout << "Refracted Color at Max Depth: Test Failed" << std::endl;

	//Refracted Color at Total Internal Reflection
	Ray ray1(create_tuple_point(0.0, 0.0, -0.5*std::sqrt(2.0)), create_tuple_vector(0.0, 1.0, 0.0));
	s.intersections[0].t = -0.5*sqrt(2.0);
	s.intersections[1].t = 0.5*sqrt(2.0);
	prepare_computations(ray1, s.intersections[1], s);
	c = shape->get_material()->refracted_color(w, s, 5);

	test = essentially_equal(Black.red, c.red) && essentially_equal(Black.green, c.green) && essentially_equal(Black.blue, c.blue);
	if (test)
		std::cout << "Total Internal Reflection: Test Passed" << std::endl;
	else
		std::cout << "Total Internal Reflection: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_refraction_index()
{
	std::shared_ptr<GeometricObject> A = create_glass_sphere();
	A->set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));
	A->get_material()->set_refractive_index(1.5);

	std::shared_ptr<GeometricObject> B = create_glass_sphere();
	B->set_transform(std::make_shared<Translation>(0.0, 0.0, -0.25));
	B->get_material()->set_refractive_index(2.0);

	std::shared_ptr<GeometricObject> C = create_glass_sphere();
	C->set_transform(std::make_shared<Translation>(0.0, 0.0, 0.25));
	C->get_material()->set_refractive_index(2.5);

	Ray ray(create_tuple_point(0.0, 0.0, -4.0), create_tuple_vector(0.0, 0.0,1.0));

	std::vector<Intersection> intersections(6);
	intersections[0].t = 2.0;
	intersections[0].object = A;
	intersections[1].t = 2.75;
	intersections[1].object = B;
	intersections[2].t = 3.25;
	intersections[2].object = C;
	intersections[3].t = 4.75;
	intersections[3].object = B;
	intersections[4].t = 5.25;
	intersections[4].object = C;
	intersections[5].t = 6;
	intersections[5].object = A;

	ShadeInfo s;
	s.intersections = intersections;
	

	//index 0;
	prepare_computations(ray, intersections[0], s);
	bool test1 = essentially_equal(s.n1, 1.0) && essentially_equal(s.n2, 1.5);
	if (test1)
		std::cout << "N1 and N2 for index 0: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 0: Test Failed" << std::endl;

	//index 1
	prepare_computations(ray, intersections[1], s);
	test1 = essentially_equal(s.n1, 1.5) && essentially_equal(s.n2, 2.0);
	if (test1)
		std::cout << "N1 and N2 for index 1: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 1: Test Failed" << std::endl;

	//imdex 2
	prepare_computations(ray, intersections[2], s);
	test1 = essentially_equal(s.n1, 2.0) && essentially_equal(s.n2, 2.5);
	if (test1)
		std::cout << "N1 and N2 for index 2: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 2: Test Failed" << std::endl;

	//index 3
	prepare_computations(ray, intersections[3], s);
	test1 = essentially_equal(s.n1, 2.5) && essentially_equal(s.n2, 2.5);
	if (test1)
		std::cout << "N1 and N2 for index 3: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 3: Test Failed" << std::endl;

	//index 4
	prepare_computations(ray, intersections[4], s);
	test1 = essentially_equal(s.n1, 2.5) && essentially_equal(s.n2, 1.5);
	if (test1)
		std::cout << "N1 and N2 for index 4: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 4: Test Failed" << std::endl;

	//index 5
	prepare_computations(ray, intersections[5], s);
	test1 = essentially_equal(s.n1, 1.5) && essentially_equal(s.n2, 1.0);
	if (test1)
		std::cout << "N1 and N2 for index 5: Test Passed" << std::endl;
	else
		std::cout << "N1 and N2 for index 5: Test Failed" << std::endl;

	//Test overpoint calc
	std::shared_ptr<GeometricObject> shape = create_glass_sphere();
	shape->set_transform(std::make_shared<Translation>(0.0,0.0,1.0));

	Ray r(create_tuple_point(0.0, 0.0, -5.0), create_tuple_vector(0.0, 0.0, 1.0));
	Intersection i1;
	i1.object = shape;
	i1.t = 5.0;

	ShadeInfo s1;
	s1.intersections = std::vector<Intersection>(1);
	s1.intersections[0] = i1;

	prepare_computations(r, i1, s1);

	test1 = (s1.under_point.z > kEpsilon*0.5) && (s1.hit_point.z < s1.under_point.z);
	if (test1)
		std::cout << "Under Point Comp: Test Passed" << std::endl;
	else
		std::cout << "Under Point Comp: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_limit_recursion()
{
	World w;
	create_default_world(w);

	ShadeInfo s;
	double t = 0.0;
	int remaining = 0;

	std::shared_ptr<GeometricObject> plane = std::make_shared<Plane>();
	plane->get_material()->set_reflective(0.5);
	plane->set_transform(std::make_shared<Translation>(0.0, -1.0, 0.0));
	w.objects.push_back(plane);

	Ray ray(create_tuple_point(0.0, 0.0, -3.0), create_tuple_vector(0.0, -0.5*std::sqrt(2.0), 0.5*std::sqrt(2.0)));
	bool hit = plane->hit(ray, t, s);

	Intersection i;
	i.t = t;
	i.object = plane;
	prepare_computations(ray, i, s);
	Color col = w.objects[2]->get_material()->reflected_color(w, s, 0);

	bool test = essentially_equal(col.red, 0.0) && essentially_equal(col.green, 0.0) && essentially_equal(col.blue, 0.0);
	if (test)
		std::cout << "Reflected Color at Max Recursive Depth: Test Passed" << std::endl;
	else
		std::cout << "Reflected Color at Max Recursive Depth: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_infinite_recursion()
{
	//Test infinite recursion
	World w;
	ShadeInfo s;

	w.lights.push_back(std::make_shared<PointLight>(create_tuple_point(0.0,0.0,0.0),Color(1.0,1.0,1.0)));

	std::shared_ptr<Plane> lower = std::make_shared<Plane>();
	lower->get_material()->set_reflective(1.0);
	lower->set_transform(std::make_shared<Translation>(0.0,-1.0,0.0));
	w.objects.push_back(lower);

	std::shared_ptr<Plane> upper = std::make_shared<Plane>();
	upper->get_material()->set_reflective(1.0);
	upper->set_transform(std::make_shared<Translation>(0.0, 1.0, 0.0));
	w.objects.push_back(upper);

	Ray r(create_tuple_point(0.0, 0.0, 0.0), create_tuple_vector(0.0, 1.0, 0.0));

	Color col = upper->get_material()->reflected_color(w, s, 2);

	std::cout << "Recursion Avoided: Test Passed" << std::endl;

	std::cout << std::endl;
}

void test_reflective_surface_hit()
{
	World w;
	create_default_world(w);

	ShadeInfo s;
	double t = 0.0;
	int remaining = 1;

	//Test non reflective
	Ray r(create_tuple_point(0.0,0.0,0.0),create_tuple_vector(0.0,0.0,1.0));
	std::shared_ptr<Phong> mat = std::make_shared<Phong>();
	mat->set_ambient(1.0);
	w.objects[1]->set_material(mat);

	bool hit = w.objects[1]->hit(r, t, s);
	Intersection i;
	i.object = w.objects[1];
	i.t = s.hit_t.first;

	prepare_computations(r, i, s);

	Color col = w.objects[1]->get_material()->reflected_color(w, s,0);

	bool test = essentially_equal(col.red, 0.0) && essentially_equal(col.green, 0.0) && essentially_equal(col.blue, 0.0);
	if (test)
		std::cout << "Reflected Color of non-reflective material: Test Passed" << std::endl;
	else
		std::cout << "Reflected Color of non-reflective material: Test Failed" << std::endl;

	//Test reflective
	std::shared_ptr<GeometricObject> plane = std::make_shared<Plane>();
	plane->get_material()->set_reflective(0.5);
	plane->set_transform(std::make_shared<Translation>(0.0,-1.0,0.0));
	w.objects.push_back(plane);
	Ray ray(create_tuple_point(0.0, 0.0, -3.0), create_tuple_vector(0.0, -0.5*std::sqrt(2.0), 0.5*std::sqrt(2.0)));
	hit = plane->hit(ray, t, s);
	i.t = t;
	i.object = plane;
	prepare_computations(ray, i, s);
	col = w.objects[2]->get_material()->reflected_color(w, s,1);

	test = floatCompareSpecified(col.red, 0.19032,0.0001) && floatCompareSpecified(col.green, 0.2379,0.0001) && floatCompareSpecified(col.blue, 0.14274,0.0001);
	if (test)
		std::cout << "Reflected Color of reflective material: Test Passed" << std::endl;
	else
		std::cout << "Reflected Color of reflective material: Test Failed" << std::endl;

	//Test Shade Hit with Reflection
	col = w.objects[2]->get_material()->shade_hit(w, s,6);
	test = floatCompareSpecified(col.red, 0.87677, 0.0001) && floatCompareSpecified(col.green, 0.92436, 0.0001) && floatCompareSpecified(col.blue, 0.82918, 0.0001);

	if (test)
		std::cout << "Shade_Hit of reflective material: Test Passed" << std::endl;
	else
		std::cout << "Shade_Hit of reflective material: Test Failed" << std::endl;

	std::cout << std::endl;
}

void test_reflection_mat()
{
	Material mat;
	ShadeInfo s;
	double t;
	//Test Reflect Vector Computation
	std::shared_ptr<GeometricObject> shape = std::make_shared<Plane>();
	Ray r(create_tuple_point(0.0,1.0,-1.0),create_tuple_vector(0.0,-0.5*std::sqrt(2.0), 0.5*std::sqrt(2.0)));
	bool hit_test = shape->hit(r, t, s);

	Intersection i;
	i.object = shape;
	i.t = std::sqrt(2.0);

	prepare_computations(r, i, s);
	bool test = essentially_equal(s.reflectv.x, 0.0) && essentially_equal(s.reflectv.y, 0.5*std::sqrt(2.0)) && essentially_equal(s.reflectv.z, 0.5*std::sqrt(2.0));
	if (test)
		std::cout << "Compute Reflection Vector: Test Passed" << std::endl;
	else
		std::cout << "Compute Reflection Vector: Test Failed" << std::endl;

	std::cout << std::endl;
}
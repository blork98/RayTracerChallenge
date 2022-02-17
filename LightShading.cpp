#include "LightShading.h"

#include "Constants.h"
#include "Ray.h"
#include "GeometricObject.h"
#include "Transform.h"
#include "Utility.h"
#include "Light.h"
#include "Material.h"

#include <iostream>
#include <iomanip>

using namespace RTC;

void light_and_shading_tests()
{
	std::cout << "Light and Shading Tests:" << std::endl << std::endl;

	test_normals();
	test_reflection();
	test_color_material();
	test_material_lighting();

	std::cout << std::endl << std::endl;
}

void test_material_lighting()
{
	std::cout << "Test Phong Lighting" << std::endl;

	//Create Material
	std::shared_ptr<Phong> phong1 = std::make_shared<Phong>();

	ShadeInfo s;
	s.hit_point = create_tuple_point(0.0f, 0.0f, 0.0f);
	s.eyev = create_tuple_vector(0.0f, 0.0f, -1.0f);
	s.normalv = create_tuple_vector(0.0f, 0.0f, -1.0f);
	std::shared_ptr<Light> light1 = std::make_shared<PointLight>(create_tuple_point(0.0f, 0.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));

	Color res = phong1->lighting(light1, s);

	bool test1 = absoluteToleranceCompare(res.red, 1.9f) && absoluteToleranceCompare(res.green, 1.9f) && absoluteToleranceCompare(res.blue, 1.9f);
	if (test1)
		std::cout << "Lighting with the eye between the light and the surface:Test Passed" << std::endl;
	else
		std::cout << "Lighting with the eye between the light and the surface:Test Failed" << std::endl;

	s.eyev = create_tuple_vector(0.0f, sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f);
	res = phong1->lighting(light1, s);
	test1 = absoluteToleranceCompare(res.red, 1.0f) && absoluteToleranceCompare(res.green, 1.0f) && absoluteToleranceCompare(res.blue, 1.0f);
	if (test1)
		std::cout << "Lighting with the eye between light and surface, eye offset 45°:Test Passed" << std::endl;
	else
		std::cout << "Lighting with the eye between light and surface, eye offset 45°:Test Failed" << std::endl;

	s.eyev = create_tuple_vector(0.0f, 0.0f, -1.0f);
	std::shared_ptr<Light> light2 = std::make_shared<PointLight>(create_tuple_point(0.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
	res = phong1->lighting(light2, s);
	test1 = floatCompareSpecified(res.red, 0.7364f,0.0001) && floatCompareSpecified(res.green, 0.7364f, 0.0001) && floatCompareSpecified(res.blue, 0.7364f, 0.0001);
	if (test1)
		std::cout << "Lighting with eye opposite surface, light offset 45:Test Passed" << std::endl;
	else
		std::cout << "Lighting with eye opposite surface, light offset 45:Test Failed" << std::endl;

	s.eyev = create_tuple_vector(0.0f, -sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f);
	res = phong1->lighting(light2, s);
	test1 = floatCompareSpecified(res.red, 1.6364f, 0.0001) && floatCompareSpecified(res.green, 1.6364f, 0.0001) && floatCompareSpecified(res.blue, 1.6364f, 0.0001);
	if (test1)
		std::cout << "Lighting with eye in the path of the reflection vector:Test Passed" << std::endl;
	else
		std::cout << "Lighting with eye in the path of the reflection vector:Test Failed" << std::endl;

	s.eyev = create_tuple_vector(0.0f, 0.0f, -1.0f);
	std::shared_ptr<Light> light3 = std::make_shared<PointLight>(create_tuple_point(0.0f, 0.0f, 10.0f), Color(1.0f, 1.0f, 1.0f));
	res = phong1->lighting(light3, s);
	test1 = floatCompareSpecified(res.red, 0.1f, 0.0001) && floatCompareSpecified(res.green, 0.1f, 0.0001) && floatCompareSpecified(res.blue, 0.1f, 0.0001);

	std::cout << std::endl << std::endl;
}

void test_color_material()
{
	std::cout << "Test Light and Material" << std::endl;

	Tuple position = create_tuple_point(0.0f, 0.0f, 0.0f);
	Color intensity(1.0f, 1.0f, 1.0f);
	PointLight light1(position, intensity);
	std::cout << "Test Point Light Initialization" << std::endl;

	Sphere sphere(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

	std::cout << "Test Sphere Initialization with default Material" << std::endl;

	std::shared_ptr<Phong> material1 = std::make_shared<Phong>();
	material1->set_ambient(2.0);
	sphere.set_material(material1);

	std::cout << "Test Sphere with assigned Material" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_reflection()
{
	std::cout << "Reflection Tests:" << std::endl;

	Tuple vector = create_tuple_vector(1.0f, -1.0f, 0.0f);
	Tuple normal = create_tuple_vector(0.0f, 1.0f, 0.0f);
	Tuple r = reflect(vector, normal);

	bool test1 = essentially_equal(r.x, 1.0f) && essentially_equal(r.y, 1.0f) && essentially_equal(r.z, 0.0f);

	if (test1)
		std::cout << "Test Vector Reflection 45 deg: Test Passed" << std::endl;
	else
		std::cout << "Test Vector Reflection 45 deg: Test Failed" << std::endl;

	vector = create_tuple_vector(0.0f, -1.0f, 0.0f);
	normal = create_tuple_vector(sqrtf(2.0f)/2.0f, sqrtf(2.0f) / 2.0f, 0.0f);
	r = reflect(vector, normal);

	test1 = floatCompareSpecified(r.x, 1.0f,0.00001) && floatCompareSpecified(r.y, 0.0f,0.00001) && absoluteToleranceCompare(r.z, 0.0f);

	if (test1)
		std::cout << "Test Vector Reflection Slanted Surface: Test Passed" << std::endl;
	else
		std::cout << "Test Vector Reflection Slanted Surface: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_normals()
{
	std::cout << "Normalt Tests:" << std::endl;

	Sphere sphere(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	Tuple point1 = create_tuple_point(1.0f, 0.0f, 0.0f);
	Tuple normal_vector = sphere.get_normal(point1);

	bool test1 = essentially_equal(1.0f, normal_vector.x) && essentially_equal(0.0f, normal_vector.y) && essentially_equal(0.0f, normal_vector.z);

	if (test1)
		std::cout << "Normal on a Sphere along x-axis: Test passed" << std:: endl;
	else
		std::cout << "Normal on a Sphere along x-axis: Test failed" << std::endl;

	point1 = create_tuple_point(0.0f, 1.0f, 0.0f);
	normal_vector = sphere.get_normal(point1);
	test1 = essentially_equal(0.0f, normal_vector.x) && essentially_equal(1.0f, normal_vector.y) && essentially_equal(0.0f, normal_vector.z);

	if (test1)
		std::cout << "Normal on a Sphere along y-axis: Test passed" << std::endl;
	else
		std::cout << "Normal on a Sphere along y-axis: Test failed" << std::endl;

	point1 = create_tuple_point(0.0f, 0.0f, 1.0f);
	normal_vector = sphere.get_normal(point1);
	test1 = essentially_equal(0.0f, normal_vector.x) && essentially_equal(0.0f, normal_vector.y) && essentially_equal(1.0f, normal_vector.z);

	if (test1)
		std::cout << "Normal on a Sphere along z-axis: Test passed" << std::endl;
	else
		std::cout << "Normal on a Sphere along z-axis: Test failed" << std::endl;

	point1 = create_tuple_point(sqrtf(3.0f)/3.0f, sqrtf(3.0f) / 3.0f, sqrtf(3.0f) / 3.0f);
	normal_vector = sphere.get_normal(point1);
	test1 = floatCompareSpecified(sqrtf(3.0f) / 3.0f, normal_vector.x,0.00001) && 
		floatCompareSpecified(sqrtf(3.0f) / 3.0f, normal_vector.y,0.00001) && 
		floatCompareSpecified(sqrtf(3.0f) / 3.0f, normal_vector.z,0.00001);

	if (test1)
		std::cout << "Normal on a Sphere along nonaxial point: Test passed" << std::endl;
	else
		std::cout << "Normal on a Sphere along nonaxial point: Test failed" << std::endl;

	bool test2 = essentially_equal(1.0f, vector_magnitude(normal_vector));

	if (test2)
		std::cout << "Normal Vector is normalized: Test passed" << std::endl;
	else
		std::cout << "Normal Vector is normalized: Test failed" << std::endl;

	//Transformed Normal
	std::shared_ptr<Transform> transform = std::make_shared<Translation>(0.0f,1.0f,0.0f);
	sphere.set_transform(transform);
	normal_vector = sphere.get_normal(create_tuple_point(0.0f,1.7071100,-0.7071100));

	std::cout << "Test Normal on Translated Sphere: "<<std::endl;
	std::cout <<std::setprecision(5)<< "x: " << normal_vector.x << "  y: " << normal_vector.y << " z: " << normal_vector.z << std::endl;

	//Transformed Sphere
	std::vector<std::shared_ptr<Transform>> transforms;
	transforms.push_back(std::make_shared<Scaling>(1.0f,0.5f,1.0f));
	Rotation rot;
	rot.rotate_y(M_PI / 5.0);
	transforms.push_back(std::make_shared<Rotation>(rot));
	
	std::shared_ptr<Transform> transform2 = std::make_shared<CompoundTransform>(transforms);
	sphere.set_transform(transform2);
	normal_vector = sphere.get_normal(create_tuple_point(0.0f, sqrt(2)/2.0, -sqrt(2) / 2.0));

	std::cout << "Test Normal on Transformed Sphere: " << std::endl;
	std::cout <<std::fixed<< std::setprecision(5) << "x: " << normal_vector.x << "  y: " << normal_vector.y << " z: " << normal_vector.z << std::endl;

	std::cout << std::endl << std::endl;
}
#include "Constants.h"
#include "SceneCreation.h"
#include "GeometricObject.h"
#include "World.h"
#include "Tuple.h"
#include "Ray.h"
#include "Utility.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"


#include <iostream>
#include <iomanip>
#include <cmath>

namespace RTC
{

	void scene_tests()
	{
		std::cout << "Scene Creation Tests:" << std::endl << std::endl;

		test_default_world();
		test_world_intersections();
		test_shading();
		test_world();
		test_view_transform();
		test_camera();
		test_camera_render();

		std::cout << std::endl << std::endl;
	}

	void test_camera_render()
	{
		std::cout << "Camera Render Test:" << std::endl << std::endl;

		World world;
		create_default_world(world);

		Camera camera(11, 11, M_PI_2);
		Canvas image(camera.get_hsize(), camera.get_vsize());

		Tuple from = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple to = create_tuple_point(0.0f, 0.0f, 0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);
		std::shared_ptr<Transform> trans = std::make_shared<ViewTransform>(from, to, up);
		camera.set_transform(trans);
		camera.render(world, image);

		Color color = image(5, 5);

		bool test1 = floatCompareSpecified(color.red, 0.38066, 0.0001) &&
			floatCompareSpecified(color.green, 0.47583, 0.0001) &&
			floatCompareSpecified(color.blue, 0.2855, 0.0001);

		if (test1)
			std::cout << "Camera Render: Test Passed" << std::endl;
		else
			std::cout << "Camera Render: Test Failed" << std::endl;

		std::cout << std::endl << std::endl;
	}

	void test_camera()
	{
		std::cout << "Camera Tests:" << std::endl << std::endl;

		//Constructing a Camera
		Camera camera(160, 120, M_PI_2);
		std::cout << "Test Camera Initialization....." << std::endl;

		//Pixel Size Calc
		Camera camera1(200, 125, M_PI_2);
		bool test1 = floatCompareSpecified(camera1.get_pixel_size(), 0.01, 0.000001);
		if (test1)
			std::cout << "Test Pixel Size for Horizontal Canvas: Test Passed" << std::endl;
		else
			std::cout << "Test Pixel Size for Horizontal Canvas: Test Failed" << std::endl;

		Camera camera2(125, 200, M_PI_2);
		test1 = floatCompareSpecified(camera2.get_pixel_size(), 0.01, 0.000001);
		if (test1)
			std::cout << "Test Pixel Size for Vertical Canvas: Test Passed" << std::endl;
		else
			std::cout << "Test Pixel Size for Vertical Canvas: Test Failed" << std::endl;

		//Ray for Pixel Test
		Camera camera3(201, 101, M_PI_2);
		Ray ray1 = camera3.ray_for_pixel(100, 50);

		bool testRayOrigin = absoluteToleranceCompare(ray1.get_origin().x, 0.0f) &&
			absoluteToleranceCompare(ray1.get_origin().y, 0.0f) &&
			absoluteToleranceCompare(ray1.get_origin().z, 0.0f);

		bool testRayDirection = absoluteToleranceCompare(ray1.get_direction().x, 0.0f) &&
			absoluteToleranceCompare(ray1.get_direction().y, 0.0f) &&
			absoluteToleranceCompare(ray1.get_direction().z, -1.0f);

		if (testRayDirection&&testRayOrigin)
			std::cout << "Construct Ray through center of canvas: Test Passed" << std::endl;
		else
			std::cout << "Construct Ray through center of canvas: Test Failed" << std::endl;

		ray1 = camera3.ray_for_pixel(0, 0);
		testRayOrigin = absoluteToleranceCompare(ray1.get_origin().x, 0.0f) &&
			absoluteToleranceCompare(ray1.get_origin().y, 0.0f) &&
			absoluteToleranceCompare(ray1.get_origin().z, 0.0f);
		testRayDirection = floatCompareSpecified(ray1.get_direction().x, 0.66519f,0.00001) &&
			floatCompareSpecified(ray1.get_direction().y, 0.33259f,0.00001) &&
			floatCompareSpecified(ray1.get_direction().z, -0.66851f,0.00001);

		if (testRayDirection&&testRayOrigin)
			std::cout << "Construct Ray through corner of canvas: Test Passed" << std::endl;
		else
			std::cout << "Construct Ray through corner of canvas: Test Failed" << std::endl;

		std::vector < std::shared_ptr<Transform >> transforms(2);
		std::shared_ptr<Rotation> trans1 = std::make_shared<Rotation>();
		trans1->rotate_y(M_PI_4);
		std::shared_ptr<Transform> trans2 = std::make_shared<Translation>(0.0f,-2.0f,5.0f);
		transforms[1] = trans1;
		transforms[0] = trans2;
		std::shared_ptr<Transform> trans3 = std::make_shared<CompoundTransform>(transforms);

		camera3.set_transform(trans3);
		ray1 = camera3.ray_for_pixel(100, 50);

		testRayOrigin = absoluteToleranceCompare(ray1.get_origin().x, 0.0f) &&
			absoluteToleranceCompare(ray1.get_origin().y, 2.0f) &&
			absoluteToleranceCompare(ray1.get_origin().z, -5.0f);
			
		testRayDirection = floatCompareSpecified(ray1.get_direction().x, std::sqrt(2)*0.5, 0.00001) &&
			floatCompareSpecified(ray1.get_direction().y, 0.0f, 0.00001) &&
			floatCompareSpecified(ray1.get_direction().z, -std::sqrt(2)*0.5, 0.00001);

		if (testRayDirection&&testRayOrigin)
			std::cout << "Construct Ray when Camera is Transformed: Test Passed" << std::endl;
		else
			std::cout << "Construct Ray when Camera is Transformed: Test Failed" << std::endl;

		std::cout << std::endl << std::endl;
	}

	void test_view_transform()
	{
		std::cout << "View Transformation Tests:" << std::endl;

		//Default Orientation
		Tuple from = create_tuple_point(0.0f, 0.0f, 0.0f);
		Tuple to = create_tuple_point(0.0f, 0.0f, -1.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);
		ViewTransform view1(from, to, up);

		Matrix4 mat1 = view1.get_transform();

		std::cout << "Transformation for Defualt Orientation:" << std::endl << std::endl;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				std::cout << mat1.m[y][x] << "           ";
			}
			std::cout << std::endl;
		}

		//Positive Z Direction
		from = create_tuple_point(0.0f, 0.0f, 0.0f);
		to = create_tuple_point(0.0f, 0.0f, 1.0f);
		up = create_tuple_vector(0.0f, 1.0f, 0.0f);
		ViewTransform view2(from, to, up);

		mat1 = view2.get_transform();
		std::cout << "Transformation for Positive Z Direction:" << std::endl << std::endl;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				std::cout << mat1.m[y][x] << "           ";
			}
			std::cout << std::endl;
		}

		//Moves the world
		from = create_tuple_point(0.0f, 0.0f, 8.0f);
		to = create_tuple_point(0.0f, 0.0f, 0.0f);
		up = create_tuple_vector(0.0f, 1.0f, 0.0f);
		ViewTransform view3(from, to, up);

		mat1 = view3.get_transform();
		std::cout << "Transformation Moves the World:" << std::endl << std::endl;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				std::cout << mat1.m[y][x] << "           ";
			}
			std::cout << std::endl;
		}

		//Arbitrary Transformation
		from = create_tuple_point(1.0f, 3.0f, 2.0f);
		to = create_tuple_point(4.0f, -2.0f, 8.0f);
		up = create_tuple_vector(1.0f, 1.0f, 0.0f);
		ViewTransform view4(from, to, up);

		mat1 = view4.get_transform();
		std::cout << "Arbitrary View Transformation:" << std::endl << std::endl;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				std::cout<<std::setprecision(6) << mat1.m[y][x] << "           ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;

	}

	void test_world()
	{
		std::cout << "World Tests:" << std::endl;

		World world;
		create_default_world(world);

		//Test Ray miss
		Tuple ray_origin1 = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple ray_direction1 = create_tuple_vector(0.0f, 1.0f, 0.0f);
		Ray ray1(ray_origin1, ray_direction1);

		Color color1 = world.color_at(ray1,1);

		bool test1 = floatCompareSpecified(color1.red, 0.0f, 0.0001) && floatCompareSpecified(color1.green, 0.0f, 0.0001) && floatCompareSpecified(color1.blue, 0.0f, 0.0001);
		if (test1)
			std::cout << "Color Ray Miss: Test Passed" << std::endl;
		else
			std::cout << "Color Ray Miss: Test Failed" << std::endl;

		//Test Ray hit
		Tuple ray_origin2 = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple ray_direction2 = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray2(ray_origin2, ray_direction2);

		color1 = world.color_at(ray2,1);
		test1 = floatCompareSpecified(color1.red, 0.38066f, 0.0001) && floatCompareSpecified(color1.green, 0.47583f, 0.0001) && floatCompareSpecified(color1.blue, 0.2855f, 0.0001);
		if (test1)
			std::cout << "Color Ray Hit: Test Passed" << std::endl;
		else
			std::cout << "Color Ray Hit: Test Failed" << std::endl;

		//Test inner hit
		Tuple ray_origin3 = create_tuple_point(0.0f, 0.0f, 0.75f);
		Tuple ray_direction3 = create_tuple_vector(0.0f, 0.0f, -1.0f);
		Ray ray3(ray_origin3, ray_direction3);

		std::shared_ptr<Phong> p1 = std::dynamic_pointer_cast<Phong>(world.objects[0]->get_material());
		if (p1)
			p1->set_ambient(1.0f);

		p1 = std::dynamic_pointer_cast<Phong>(world.objects[1]->get_material());
		if (p1)
		{
			p1->set_ambient(1.0f);
			p1->set_color(Color(0.5f, 0.5f, 0.5f));
		}

		color1 = world.color_at(ray3,1);
		test1 = floatCompareSpecified(color1.red, 0.5f, 0.0001) && floatCompareSpecified(color1.green, 0.5f, 0.0001) && floatCompareSpecified(color1.blue, 0.5f, 0.0001);
		if (test1)
			std::cout << "Color Ray Inner Hit: Test Passed" << std::endl;
		else
			std::cout << "Color Ray Inner Hit: Test Failed" << std::endl;

		std::cout << std::endl << std::endl;
	}

	void test_shading()
	{
		std::cout << "Shading Tests:" << std::endl;

		World world;
		create_default_world(world);

		//Shading an Intersection Outside
		Tuple ray_origin = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple ray_direction = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray(ray_origin, ray_direction);

		ShadeInfo s;
		double t = 0.0;

		bool hit = world.objects[0]->hit(ray,t, s);
		Intersection intersection;
		intersection.t = s.hit_t.first;
		intersection.point = s.hit_points.first;
		intersection.object = s.object;

		prepare_computations(ray, intersection, s);

		Color color = s.object->get_material()->shade_hit(world, s,1);

		bool test1 = floatCompareSpecified(color.red, 0.38066, 0.0001)&& floatCompareSpecified(color.green, 0.47583, 0.0001)&& floatCompareSpecified(color.blue, 0.2855, 0.0001);

		if (test1)
			std::cout << "Test Shading Intersection outside: Test Passed" << std::endl;
		else
			std::cout << "Test Shading Intersection outside: Test Failed" << std::endl;

		//Shading an Intersection Outside
		Tuple ray_origin2 = create_tuple_point(0.0f, 0.0f, 0.0f);
		Tuple ray_direction2 = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray2(ray_origin2, ray_direction2);

		std::shared_ptr<Light> light1 = std::make_shared<PointLight>(create_tuple_point(0.0f, 0.25f, 0.0f), Color(1.0f, 1.0f, 1.0f));
		world.lights[0] = light1;
		ShadeInfo s2;

		hit = world.objects[1]->hit(ray2, t, s2);
		intersection.t = s2.hit_t.second;
		intersection.point = s2.hit_points.second;
		intersection.object = s2.object;

		prepare_computations(ray2, intersection, s2);
		color = s2.object->get_material()->shade_hit(world, s2,1);

		test1 = floatCompareSpecified(color.red, 0.90498, 0.0001) && floatCompareSpecified(color.green, 0.90498, 0.0001) && floatCompareSpecified(color.blue, 0.90498, 0.0001);

		if (test1)
			std::cout << "Test Shading Intersection inside: Test Passed" << std::endl;
		else
			std::cout << "Test Shading Intersection inside: Test Failed" << std::endl;

		std::cout << std::endl << std::endl;
	}

	void test_default_world()
	{
		//Test Default Creation
		std::cout << "Default World Creation" << std::endl;

		World world;
		create_default_world(world);

		std::cout << "Defualt World Initialization Test...." << std::endl;

		//Test World Intersection
		Tuple ray_origin = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple ray_direction = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray(ray_origin,ray_direction);
		ShadeInfo s;

		std::vector<Intersection> xs = world.intersect_world(ray, s);

		bool test1 = essentially_equal(xs[0].t, 4.0f) && essentially_equal(xs[1].t, 4.5f) && essentially_equal(xs[2].t, 5.5f) && essentially_equal(xs[3].t, 6.0f);

		if (test1)
			std::cout << "Intersect World witha Ray: Test passed" << std::endl;
		else
			std::cout << "Intersect World witha Ray: Test failed" << std::endl;

		//Test Pre-Computation
		prepare_computations(ray, xs[0], s);

		test1 = essentially_equal(xs[0].t, 4.0f);
		bool test2 = essentially_equal(s.hit_point.x, 0.0f) && essentially_equal(s.hit_point.y, 0.0f) && essentially_equal(s.hit_point.z, -1.0f);
		bool test3 = essentially_equal(s.normalv.x, 0.0f) && essentially_equal(s.normalv.y, 0.0f) && essentially_equal(s.normalv.z, -1.0f);
		bool test4 = essentially_equal(s.eyev.x, 0.0f) && essentially_equal(s.eyev.y, 0.0f) && essentially_equal(s.eyev.z, -1.0f);

		if (test1&&test2&&test3&&test4)
			std::cout << "Test Pre Computation: Test Passed" << std::endl;
		else
			std::cout << "Test Pre Computation: Test Failed" << std::endl;

		//Test outside hit
		test1 = s.inside;
		if (!test1)
			std::cout << "Test outside hit: Test Passed" << std::endl;
		else
			std::cout << "Test outside hit: Test Failed" << std::endl;

		//Test inside hit
		Tuple ray_origin2 = create_tuple_point(0.0f, 0.0f, 0.0f);
		Tuple ray_direction2 = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray2(ray_origin2, ray_direction2);

		ShadeInfo s1;
		double t = 0.0;
		Sphere sphere1(create_tuple_point(0.0f,0.0f,0.0f),1.0f);
		bool hit = sphere1.hit(ray2, t, s1);
		Intersection intersection2;
		intersection2.t = s1.hit_t.second;
		intersection2.point = s1.hit_points.second;
		intersection2.object = s1.object;
		prepare_computations(ray2, intersection2, s1);

		test1 = s1.inside;
		test2 = essentially_equal(s1.hit_point.x, 0.0f) && essentially_equal(s1.hit_point.y, 0.0f) && essentially_equal(s1.hit_point.z, 1.0f);
		test3 = essentially_equal(s1.normalv.x, 0.0f) && essentially_equal(s1.normalv.y, 0.0f) && essentially_equal(s1.normalv.z, -1.0f);
		test4 = essentially_equal(s1.eyev.x, 0.0f) && essentially_equal(s1.eyev.y, 0.0f) && essentially_equal(s1.eyev.z, -1.0f);

		if (test1&&test2&&test3&&test4)
			std::cout << "Test inside hit: Test Passed" << std::endl;
		else
			std::cout << "Test inside hit: Test Failed" << std::endl;

		std::cout << std::endl << std::endl;

	}

	void test_world_intersections()
	{
		World world;
		create_default_world(world);

		Tuple ray_origin = create_tuple_point(0.0f, 0.0f, 6.0f);
		Tuple ray_direction = create_tuple_vector(0.0f, 0.0f, 1.0f);
		Ray ray(ray_origin, ray_direction);
		ShadeInfo s;

		std::vector<Intersection> xs = world.intersect_world(ray, s);
		Intersection intersection;
		bool hit = nearest_hit(xs, intersection);

		Color c = world.color_at(ray, 5);
	}

}
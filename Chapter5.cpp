#include "Constants.h"
#include "Chapter5.h"
#include "GeometricObject.h"
#include "Canvas.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "Utility.h"
#include "Transform.h"
#include "World.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

namespace RTC
{
	void draw_red_sphere()
	{
		//start ray at z= -5
		Tuple ray_origin= create_tuple_point(0.0f, 0.0f, -5.0f);

		//wall at z = 10
		float wall_z = 10.0;
		float wall_size = 7.0f;

		unsigned int canvas_pixels = 400;
		float pixel_size = wall_size / canvas_pixels;
		float half = wall_size / 2.0f;

		Canvas canvas(canvas_pixels, canvas_pixels);
		Color color(1.0f, 0.0f, 0.0f);
		Sphere sphere(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		float world_y = 0.0f, world_x = 0.0f;

		Tuple position;
		Ray ray;
		ShadeInfo s;
		Intersection i;
		double t = 0.0;

		for (unsigned int y = 0; y < canvas_pixels; ++y)
		{
			world_y = half - pixel_size*y;

			for (unsigned int x = 0; x < canvas_pixels; ++x)
			{
				world_x = -half + pixel_size*x;
				position = create_tuple_point(world_x,world_y,wall_z);
				ray = Ray(ray_origin,normalize_vector(position-ray_origin));

				if (sphere.hit(ray, t, s))
				{
					canvas(x, y) = color;
				}

			}
		}

		std::ofstream outFile1("RedSphere.ppm");
		canvas.write_PPM(outFile1);
		outFile1.close();
	}

	void render_phong_sphere()
	{
		//Create Sphere
		Sphere sphere(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		std::shared_ptr<Phong> material = std::make_shared<Phong>();
		material->set_color(Color(1.0f,0.2f,1.0f));
		sphere.set_material(material);

		//Create Light
		std::shared_ptr<Light> light = std::make_shared<PointLight>(create_tuple_point(-10.0f,10.0f,-10.0f),Color(1.0f,1.0f,1.0f));

		//Scene Settings
		//start ray at z= -5
		Tuple ray_origin = create_tuple_point(0.0f, 0.0f, -5.0f);

		//wall at z = 10
		float wall_z = 10.0;
		float wall_size = 7.0f;

		unsigned int canvas_pixels = 400;
		float pixel_size = wall_size / canvas_pixels;
		float half = wall_size / 2.0f;

		Canvas canvas(canvas_pixels, canvas_pixels);

		float world_y = 0.0f, world_x = 0.0f;

		Tuple position, pos;
		Ray ray;
		ShadeInfo s;
		Intersection i;
		double t = 0.0;

		for (unsigned int y = 0; y < canvas_pixels; ++y)
		{
			world_y = half - pixel_size*y;

			for (unsigned int x = 0; x < canvas_pixels; ++x)
			{
				world_x = -half + pixel_size*x;
				position = create_tuple_point(world_x, world_y, wall_z);
				ray = Ray(ray_origin, normalize_vector(position - ray_origin));

				if (sphere.hit(ray, t, s))
				{
					pos = ray.position(t);
					s.normalv = sphere.get_normal(s.hit_point);
					s.eyev = -1.0f*ray.get_direction();
					canvas(x, y) = sphere.get_material()->lighting(light, s);
				}

			}
		}

		std::ofstream outFile1("PhongSphere.ppm");
		canvas.write_PPM(outFile1);
		outFile1.close();

	}

	void render_multi_sphere()
	{
		//Create Fllor
		std::shared_ptr<GeometricObject> floor = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		floor->set_transform(std::make_shared<Scaling>(10.0f,0.01f,10.0f));
		
		std::shared_ptr<Phong> floor_mat = std::make_shared<Phong>();
		floor_mat->set_color(Color(1.0f,0.9f,0.9f));
		floor_mat->set_specular(0.0f);
		floor->set_material(floor_mat);

		//Create Left Wall
		std::shared_ptr<GeometricObject> left_wall = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		left_wall->set_material(floor_mat);

		std::vector<std::shared_ptr<Transform>> transforms_lw(4);

		transforms_lw[0] = std::make_shared<Scaling>(10.0f, 0.01f, 10.0f);
		transforms_lw[3] = std::make_shared<Translation>(0.0f,0.0f,5.0f);
		
		std::shared_ptr<Rotation> rot1 = std::make_shared<Rotation>();
		rot1->rotate_x(M_PI_2);
		transforms_lw[1] = rot1;

		std::shared_ptr<Rotation> rot2 = std::make_shared<Rotation>();
		rot2->rotate_y(-M_PI_4);
		transforms_lw[2] = rot2;

		std::shared_ptr<Transform> left_trans = std::make_shared<CompoundTransform>(transforms_lw);
		left_wall->set_transform(left_trans);

		//Create Right Wall
		std::shared_ptr<GeometricObject> right_wall = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
		right_wall->set_material(floor_mat);

		std::vector<std::shared_ptr<Transform>> transforms_rw(4);

		transforms_rw[0] = std::make_shared<Scaling>(10.0f, 0.01f, 10.0f);
		transforms_rw[3] = std::make_shared<Translation>(0.0f, 0.0f, 5.0f);
		transforms_rw[1] = rot1;

		std::shared_ptr<Rotation> rot3 = std::make_shared<Rotation>();
		rot3->rotate_y(M_PI_4);
		transforms_rw[2] = rot3;

		std::shared_ptr<Transform> right_trans = std::make_shared<CompoundTransform>(transforms_rw);
		right_wall->set_transform(right_trans);

		//Create Right Sphere
		std::shared_ptr<GeometricObject> middle = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> middle_mat = std::make_shared<Phong>();
		middle_mat->set_color(Color(0.5f, 1.0f, 0.1f));
		middle_mat->set_specular(0.3f);
		middle_mat->set_diffuse(0.7f);
		middle->set_material(middle_mat);

		std::vector<std::shared_ptr<Transform>> transforms_m(2);
		transforms_m[0] = std::make_shared<Scaling>(0.5f,0.5f,0.5f);
		transforms_m[1] = std::make_shared<Translation>(1.5f,0.5f,-0.5f);
		middle->set_transform(std::make_shared<CompoundTransform>(transforms_m));

		//Create middle sphere
		std::shared_ptr<GeometricObject> large = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> large_mat = std::make_shared<Phong>();
		large_mat->set_color(Color(0.1f, 1.0f, 0.5f));
		large_mat->set_specular(0.3f);
		large_mat->set_diffuse(0.7f);
		large->set_material(large_mat);

		large->set_transform(std::make_shared<Translation>(-0.5f, 1.0f, 0.5f));

		//Create small sphere
		std::shared_ptr<GeometricObject> small = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> small_mat = std::make_shared<Phong>();
		small_mat->set_specular(0.3f);
		small_mat->set_diffuse(0.7f);
		small_mat->set_color(Color(1.0f, 0.8f, 0.1f));
		small->set_material(small_mat);

		std::vector<std::shared_ptr<Transform>> transforms_s(2);
		transforms_s[0] = std::make_shared<Scaling>(0.33f, 0.33f, 0.33f);
		transforms_s[1] = std::make_shared<Translation>(-1.5f, 0.33f, -0.75f);
		small->set_transform(std::make_shared<CompoundTransform>(transforms_s));


		//Create world
		World world;
		std::vector<std::shared_ptr<GeometricObject>> objects(6);
		objects[0] = floor;
		objects[1] = left_wall;
		objects[2] = right_wall;
		objects[3] = middle;
		objects[4] = large;
		objects[5] = small;

		world.objects = objects;

		std::vector<std::shared_ptr<Light>> lights(1);
		lights[0] = std::make_shared<PointLight>(create_tuple_point(-10.0f,10.0f,-10.0f),Color(1.0f,1.0f,1.0f));
		world.lights = lights;

		Camera camera(800, 400, M_PI / 3.0);
		Canvas image(800, 400);

		Tuple from = create_tuple_point(0.0f,1.5f,-5.0f);
		Tuple to = create_tuple_point(0.0f,1.0f,0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);

		std::shared_ptr<Transform> view_trans = std::make_shared<ViewTransform>(from,to,up);
		camera.set_transform(view_trans);

		camera.render(world, image);

		std::ofstream outFile1("MultiSphere.ppm");
		image.write_PPM(outFile1);
		outFile1.close();
		
	}

	void render_sphere_plane()
	{
		//Create Right Sphere
		std::shared_ptr<GeometricObject> middle = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> middle_mat = std::make_shared<Phong>();
		middle_mat->set_color(Color(0.5f, 1.0f, 0.1f));
		middle_mat->set_specular(0.3f);
		middle_mat->set_diffuse(0.7f);
		middle->set_material(middle_mat);

		std::vector<std::shared_ptr<Transform>> transforms_m(2);
		transforms_m[0] = std::make_shared<Scaling>(0.5f, 0.5f, 0.5f);
		transforms_m[1] = std::make_shared<Translation>(1.5f, 0.5f, -0.5f);
		middle->set_transform(std::make_shared<CompoundTransform>(transforms_m));

		//Create middle sphere
		std::shared_ptr<GeometricObject> large = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> large_mat = std::make_shared<Phong>();
		large_mat->set_color(Color(0.1f, 1.0f, 0.5f));
		large_mat->set_specular(0.3f);
		large_mat->set_diffuse(0.7f);
		large->set_material(large_mat);

		large->set_transform(std::make_shared<Translation>(-0.5f, 1.0f, 0.5f));

		//Create small sphere
		std::shared_ptr<GeometricObject> small = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> small_mat = std::make_shared<Phong>();
		small_mat->set_specular(0.3f);
		small_mat->set_diffuse(0.7f);
		small_mat->set_color(Color(1.0f, 0.8f, 0.1f));
		small->set_material(small_mat);

		std::vector<std::shared_ptr<Transform>> transforms_s(2);
		transforms_s[0] = std::make_shared<Scaling>(0.33f, 0.33f, 0.33f);
		transforms_s[1] = std::make_shared<Translation>(-1.5f, 0.33f, -0.75f);
		small->set_transform(std::make_shared<CompoundTransform>(transforms_s));

		//Create Floor
		std::shared_ptr<GeometricObject> floor = std::make_shared<Plane>();
		std::shared_ptr<Phong> floor_mat = std::make_shared<Phong>();
		floor_mat->set_color(Color(1.0f, 0.9f, 0.9f));
		floor_mat->set_specular(0.0f);
		floor->set_material(floor_mat);

		//Create world
		World world;
		std::vector<std::shared_ptr<GeometricObject>> objects(4);
		objects[0] = middle;
		objects[1] = large;
		objects[2] = small;
		objects[3] = floor;

		std::vector<std::shared_ptr<Light>> lights(1);
		lights[0] = std::make_shared<PointLight>(create_tuple_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
		world.lights = lights;

		world.objects = objects;

		Camera camera(800, 400, M_PI / 3.0);
		Canvas image(800, 400);

		Tuple from = create_tuple_point(0.0f, 1.5f, -5.0f);
		Tuple to = create_tuple_point(0.0f, 1.0f, 0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);

		std::shared_ptr<Transform> view_trans = std::make_shared<ViewTransform>(from, to, up);
		camera.set_transform(view_trans);

		camera.render(world, image);

		std::ofstream outFile1("MultiSpherePlane.ppm");
		image.write_PPM(outFile1);
		outFile1.close();
	}

	void render_patterns()
	{
		//Create Floor
		std::shared_ptr<GeometricObject> floor = std::make_shared<Plane>();
		std::shared_ptr<Phong> floor_mat = std::make_shared<Phong>();
		floor_mat->set_color(Color(1.0f, 0.9f, 0.9f));
		floor_mat->set_specular(0.0f);
		floor_mat->set_reflective(0.5);
		floor_mat->set_pattern(std::make_shared<CheckerPattern>(White,Black));
		//floor_mat->set_pattern(std::make_shared<RadialGradient>(White, Black));
		floor->set_material(floor_mat);

		//Create Wall;
		std::shared_ptr<GeometricObject> wall = std::make_shared<Plane>();
		std::shared_ptr<Phong> wall_mat = std::make_shared<Phong>();
		wall_mat->set_color(Color(1.0f, 0.9f, 0.9f));
		wall_mat->set_specular(0.0f);
		wall_mat->set_reflective(1.0);
		//wall_mat->set_pattern(std::make_shared<RingPattern>(White, Black));
		//wall_mat->set_pattern(std::make_shared<RadialGradient>(White, Black));
		wall->set_material(wall_mat);


		std::vector<std::shared_ptr<Transform>> transforms_rw(2);

		std::shared_ptr<Rotation> rot1 = std::make_shared<Rotation>();
		rot1->rotate_x(M_PI_2);

		//transforms_rw[0] = std::make_shared<Translation>(0.0f, 0.0f, 0.0f);
		transforms_rw[0] = rot1;
		transforms_rw[1] = std::make_shared<Translation>(0.0f, 0.0f, 5.0f);


		std::shared_ptr<Transform> right_trans = std::make_shared<CompoundTransform>(transforms_rw);
		wall->set_transform(right_trans);

		//Create middle sphere
		std::shared_ptr<GeometricObject> large = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> large_mat = std::make_shared<Phong>();
		large_mat->set_color(Color(0.1f, 1.0f, 0.5f));
		large_mat->set_specular(0.3f);
		large_mat->set_diffuse(0.7f);
		large_mat->set_pattern(std::make_shared<StripePattern>(Color(1.0,0.0,0.0),Color(0.0,1.0,0.0)));
		large->set_material(large_mat);

		large->set_transform(std::make_shared<Translation>(-0.5f, 1.0f, 0.5f));

		//Create Right Sphere
		std::shared_ptr<GeometricObject> middle = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> middle_mat = std::make_shared<Phong>();
		middle_mat->set_color(Color(0.5f, 1.0f, 0.1f));
		middle_mat->set_specular(0.3f);
		middle_mat->set_diffuse(0.7f);
		middle_mat->set_pattern(std::make_shared<GradientPattern>(Color(1.0,0.0,0.0),Color(0.0,0.0,1.0)));
		middle->set_material(middle_mat);

		std::vector<std::shared_ptr<Transform>> transforms_m(2);
		transforms_m[0] = std::make_shared<Scaling>(0.5f, 0.5f, 0.5f);
		transforms_m[1] = std::make_shared<Translation>(1.5f, 0.5f, -0.5f);
		middle->set_transform(std::make_shared<CompoundTransform>(transforms_m));

		//Create small sphere
		std::shared_ptr<GeometricObject> small = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> small_mat = std::make_shared<Phong>();
		small_mat->set_specular(0.3f);
		small_mat->set_diffuse(0.7f);
		small_mat->set_color(Color(1.0f, 0.8f, 0.1f));
		small_mat->set_pattern(std::make_shared<StripePattern>(White,Black));
		small->set_material(small_mat);

		std::vector<std::shared_ptr<Transform>> transforms_s(2);
		transforms_s[0] = std::make_shared<Scaling>(0.33f, 0.33f, 0.33f);
		transforms_s[1] = std::make_shared<Translation>(-1.5f, 0.33f, -0.75f);
		small->set_transform(std::make_shared<CompoundTransform>(transforms_s));

		//Create world
		World world;
		std::vector<std::shared_ptr<GeometricObject>> objects(5);
		objects[0] = floor;
		objects[1] = wall;
		objects[2] = large;
		objects[3] = middle;
		objects[4] = small;

		std::vector<std::shared_ptr<Light>> lights(1);
		lights[0] = std::make_shared<PointLight>(create_tuple_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
		world.lights = lights;

		world.objects = objects;

		Camera camera(800, 400, M_PI / 3.0);
		Canvas image(800, 400);

		Tuple from = create_tuple_point(0.0f, 1.5f, -5.0f);
		Tuple to = create_tuple_point(0.0f, 1.0f, 0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);

		std::shared_ptr<Transform> view_trans = std::make_shared<ViewTransform>(from, to, up);
		camera.set_transform(view_trans);

		camera.render(world, image);

		std::ofstream outFile1("Pattern.ppm");
		image.write_PPM(outFile1);
		outFile1.close();
	}

	void render_reflection_test()
	{
		//Create Floor
		std::shared_ptr<GeometricObject> floor = std::make_shared<Plane>();
		std::shared_ptr<Phong> floor_mat = std::make_shared<Phong>();
		floor_mat->set_color(Color(1.0f, 0.9f, 0.9f));
		floor_mat->set_specular(0.0f);
		floor_mat->set_reflective(0.8);
		floor_mat->set_pattern(std::make_shared<CheckerPattern>(White, Black));
		//floor_mat->set_pattern(std::make_shared<RadialGradient>(White, Black));
		floor->set_material(floor_mat);

		//Create Wall;
		std::shared_ptr<GeometricObject> wall = std::make_shared<Plane>();
		std::shared_ptr<Phong> wall_mat = std::make_shared<Phong>();
		wall_mat->set_color(Color(1.0f, 0.9f, 0.9f));
		wall_mat->set_specular(0.0f);
		wall_mat->set_reflective(0.4);
		wall_mat->set_pattern(std::make_shared<CheckerPattern>(White, Black));
		//wall_mat->set_pattern(std::make_shared<RadialGradient>(White, Black));
		wall->set_material(wall_mat);

		std::vector<std::shared_ptr<Transform>> transforms_rw(2);

		std::shared_ptr<Rotation> rot1 = std::make_shared<Rotation>();
		rot1->rotate_x(M_PI_2);

		//transforms_rw[0] = std::make_shared<Translation>(0.0f, 0.0f, 0.0f);
		transforms_rw[0] = rot1;
		transforms_rw[1] = std::make_shared<Translation>(0.0f, 0.0f, 5.0f);


		std::shared_ptr<Transform> right_trans = std::make_shared<CompoundTransform>(transforms_rw);
		wall->set_transform(right_trans);

		//Create middle sphere
		std::shared_ptr<GeometricObject> large = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> large_mat = std::make_shared<Phong>();
		large_mat->set_color(Color(0.1f, 1.0f, 0.5f));
		large_mat->set_specular(0.3f);
		large_mat->set_diffuse(0.7f);
		large_mat->set_reflective(0.5);
		large_mat->set_pattern(std::make_shared<StripePattern>(Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0)));
		large->set_material(large_mat);

		large->set_transform(std::make_shared<Translation>(-0.5f, 1.0f, 0.5f));

		//Create Right Sphere
		std::shared_ptr<GeometricObject> middle = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> middle_mat = std::make_shared<Phong>();
		middle_mat->set_color(Color(0.5f, 1.0f, 0.1f));
		middle_mat->set_specular(0.3f);
		middle_mat->set_diffuse(0.7f);
		middle_mat->set_pattern(std::make_shared<GradientPattern>(Color(1.0, 0.0, 0.0), Color(0.0, 0.0, 1.0)));
		middle->set_material(middle_mat);

		std::vector<std::shared_ptr<Transform>> transforms_m(2);
		transforms_m[0] = std::make_shared<Scaling>(0.5f, 0.5f, 0.5f);
		transforms_m[1] = std::make_shared<Translation>(1.5f, 0.5f, -0.5f);
		middle->set_transform(std::make_shared<CompoundTransform>(transforms_m));

		//Create small sphere
		std::shared_ptr<GeometricObject> small = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);

		std::shared_ptr<Phong> small_mat = std::make_shared<Phong>();
		small_mat->set_specular(0.3f);
		small_mat->set_diffuse(0.7f);
		small_mat->set_color(Color(1.0f, 0.8f, 0.1f));
		small_mat->set_pattern(std::make_shared<StripePattern>(White, Black));
		small->set_material(small_mat);

		std::vector<std::shared_ptr<Transform>> transforms_s(2);
		transforms_s[0] = std::make_shared<Scaling>(0.33f, 0.33f, 0.33f);
		transforms_s[1] = std::make_shared<Translation>(-1.5f, 0.33f, -0.75f);
		small->set_transform(std::make_shared<CompoundTransform>(transforms_s));

		//Create world
		World world;
		world.num_reflect_recurions = 5;
		std::vector<std::shared_ptr<GeometricObject>> objects(5);
		objects[0] = floor;
		objects[1] = wall;
		objects[2] = large;
		objects[3] = middle;
		objects[4] = small;

		std::vector<std::shared_ptr<Light>> lights(1);
		lights[0] = std::make_shared<PointLight>(create_tuple_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
		world.lights = lights;

		world.objects = objects;

		Camera camera(800, 400, M_PI / 3.0);
		Canvas image(800, 400);

		Tuple from = create_tuple_point(0.0f, 1.5f, -5.0f);
		Tuple to = create_tuple_point(0.0f, 1.0f, 0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);

		std::shared_ptr<Transform> view_trans = std::make_shared<ViewTransform>(from, to, up);
		camera.set_transform(view_trans);

		camera.render(world, image);

		std::ofstream outFile1("Reflect.ppm");
		image.write_PPM(outFile1);
		outFile1.close();
	}

	void render_refraction_transparency()
	{
		World w;

		//Create Wall
		std::shared_ptr<GeometricObject> wall = std::make_shared<Plane>();
		
		std::shared_ptr<Phong> wall_mat = std::make_shared<Phong>();
		wall_mat->set_ambient(0.8);
		wall_mat->set_diffuse(0.2);
		wall_mat->set_specular(0.0);
		wall_mat->set_pattern(std::make_shared<CheckerPattern>(Color(0.15,0.15,0.15),Color(0.85,0.85,0.85)));
		wall->set_material(wall_mat);

		std::vector<std::shared_ptr<Transform>> transforms_w(2);

		std::shared_ptr<Rotation> rot1 = std::make_shared<Rotation>();
		rot1->rotate_x(M_PI_2);
		transforms_w[0] = rot1;
		transforms_w[1] = std::make_shared<Translation>(0.0f, 0.0f, 10.0f);

		std::shared_ptr<Transform> wall_trans = std::make_shared<CompoundTransform>(transforms_w);
		wall->set_transform(wall_trans);
		w.objects.push_back(wall);

		//Glass Ball
		std::shared_ptr<GeometricObject> glass_ball = std::make_shared<Sphere>();

		std::shared_ptr<Phong> glass_ball_mat = std::make_shared<Phong>();
		glass_ball_mat->set_ambient(0.0);
		glass_ball_mat->set_diffuse(0.0);
		glass_ball_mat->set_specular(0.9);
		glass_ball_mat->set_shininess(300.0);
		glass_ball_mat->set_reflective(0.9);
		glass_ball_mat->set_transparency(0.9);
		glass_ball_mat->set_refractive_index(1.5);
		glass_ball_mat->set_color(Color(1.0,1.0,1.0));
		glass_ball->set_material(glass_ball_mat);
		w.objects.push_back(glass_ball);

		//Hollow Sphere
		std::shared_ptr<GeometricObject> center_sphere = std::make_shared<Sphere>();

		center_sphere->set_transform(std::make_shared<Scaling>(0.5,0.5,0.5));

		std::shared_ptr<Phong> center_sphere_mat = std::make_shared<Phong>();
		center_sphere_mat->set_ambient(0.0);
		center_sphere_mat->set_diffuse(0.0);
		center_sphere_mat->set_specular(0.9);
		center_sphere_mat->set_shininess(300.0);
		center_sphere_mat->set_reflective(0.9);
		center_sphere_mat->set_transparency(0.9);
		center_sphere_mat->set_refractive_index(1.0000034);
		center_sphere_mat->set_color(Color(1.0, 1.0, 1.0));
		center_sphere->set_material(center_sphere_mat);
		w.objects.push_back(center_sphere);

		//Create Lights
		std::vector<std::shared_ptr<Light>> lights(1);
		lights[0] = std::make_shared<PointLight>(create_tuple_point(2.0f, 10.0f, -5.0f), Color(0.9f, 0.9f, 0.9f));
		w.lights = lights;

		//Create Camera
		Camera camera(300, 300, 0.45);
		Canvas image(300, 300);

		Tuple from = create_tuple_point(0.0f, 0.0f, -5.0f);
		Tuple to = create_tuple_point(0.0f, 0.0f, 0.0f);
		Tuple up = create_tuple_vector(0.0f, 1.0f, 0.0f);

		std::shared_ptr<Transform> view_trans = std::make_shared<ViewTransform>(from, to, up);
		camera.set_transform(view_trans);

		//Reander and write to file
		camera.render(w, image);

		//Ray r = camera.ray_for_pixel(125, 125);
		//Color c = w.color_at(r, 5);

		std::ofstream outFile1("RefractTransparency.ppm");
		image.write_PPM(outFile1);
		outFile1.close();

	}
}
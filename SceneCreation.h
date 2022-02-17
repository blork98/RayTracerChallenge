#ifndef SCENECREATION_H_
#define SCENECREATION_H_

namespace RTC
{
	void scene_tests();

//Scenario: The default world
//	Given light ? point_light(point(-10, 10, -10), color(1, 1, 1))
//	And s1 ? sphere() with :
//	| material.color | (0.8, 1.0, 0.6) |
//	| material.diffuse | 0.7 |
//	| material.specular | 0.2 |
//	And s2 ? sphere() with :
//	| transform | scaling(0.5, 0.5, 0.5) |
//	When w ? default_world()
//  Then w.light = light
//	And w contains s1
//	And w contains s2

//Scenario: Intersect a world with a ray
//	Given w ? default_world()
//	And r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	When xs ? intersect_world(w, r)
//	Then xs.count = 4
//	And xs[0].t = 4
//	And xs[1].t = 4.5
//	And xs[2].t = 5.5
//	And xs[3].t = 6

//Scenario: Precomputing the state of an intersection
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And shape ? sphere()
//	And i ? intersection(4, shape)
//	When comps ? prepare_computations(i, r)
//	Then comps.t = i.t
//	And comps.object = i.object
//	And comps.point = point(0, 0, -1)
//	And comps.eyev = vector(0, 0, -1)
//	And comps.normalv = vector(0, 0, -1)

//Scenario: The hit, when an intersection occurs on the outside
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And shape ? sphere()
//	And i ? intersection(4, shape)
//	When comps ? prepare_computations(i, r)
//	Then comps.inside = false

	void test_default_world();

//Scenario: Shading an intersection
//	Given w ? default_world()
//	And r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And shape ? the first object in w
//	And i ? intersection(4, shape)
//	When comps ? prepare_computations(i, r)
//	And c ? shade_hit(w, comps)
//	Then c = color(0.38066, 0.47583, 0.2855)

//Scenario: Shading an intersection from the inside
//	Given w ? default_world()
//	And w.light ? point_light(point(0, 0.25, 0), color(1, 1, 1))
//	And r ? ray(point(0, 0, 0), vector(0, 0, 1))
//	And shape ? the second object in w
//	And i ? intersection(0.5, shape)
//	When comps ? prepare_computations(i, r)
//	And c ? shade_hit(w, comps)
//	Then c = color(0.90498, 0.90498, 0.90498)
	void test_shading();

//Scenario: The color when a ray misses
//	Given w ? default_world()
//	And r ? ray(point(0, 0, -5), vector(0, 1, 0))
//	When c ? color_at(w, r)
//	Then c = color(0, 0, 0)

//Scenario: The color when a ray hits
//	Given w ? default_world()
//	And r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	When c ? color_at(w, r)
//	Then c = color(0.38066, 0.47583, 0.2855)

	void test_world();

//Scenario: The transformation matrix for the default orientation
//	Given from ? point(0, 0, 0)
//	And to ? point(0, 0, -1)
//	And up ? vector(0, 1, 0)
//	When t ? view_transform(from, to, up)
//	Then t = identity_matrix

//Scenario: A view transformation matrix looking in positive z direction
//	Given from ? point(0, 0, 0)
//	And to ? point(0, 0, 1)
//	And up ? vector(0, 1, 0)
//	When t ? view_transform(from, to, up)
//	Then t = scaling(-1, 1, -1)

//Scenario: The view transformation moves the world
//	Given from ? point(0, 0, 8)
//	And to ? point(0, 0, 0)
//	And up ? vector(0, 1, 0)
//	When t ? view_transform(from, to, up)
//	Then t = translation(0, 0, -8)

//Scenario: An arbitrary view transformation
//	Given from ? point(1, 3, 2)
//	And to ? point(4, -2, 8)
//	And up ? vector(1, 1, 0)
//	When t ? view_transform(from, to, up)
//	Then t is the following 4x4 matrix :
//		  | -0.50709 | 0.50709 | 0.67612 | -2.36643 |
//			  | 0.76772 | 0.60609 | 0.12122 | -2.82843 |
//			  | -0.35857 | 0.59761 | -0.71714 | 0.00000 |
//			  | 0.00000 | 0.00000 | 0.00000 | 1.00000 |
	void test_view_transform();

//Scenario: Constructing a camera
//	Given hsize ? 160
//	And vsize ? 120
//	And field_of_view ? ? / 2
//	When c ? camera(hsize, vsize, field_of_view)
//	Then c.hsize = 160
//	And c.vsize = 120
//	And c.field_of_view = ? / 2
//	And c.transform = identity_matrix

//Scenario: The pixel size for a horizontal canvas
//	Given c ? camera(200, 125, ? / 2)
//	Then c.pixel_size = 0.01
//Scenario : The pixel size for a vertical canvas
//	Given c ? camera(125, 200, ? / 2)
//	Then c.pixel_size = 0.01

//Scenario: Constructing a ray through the center of the canvas
//	Given c ? camera(201, 101, ? / 2)
//	When r ? ray_for_pixel(c, 100, 50)
//	Then r.origin = point(0, 0, 0)
//	And r.direction = vector(0, 0, -1)

//Scenario: Constructing a ray through a corner of the canvas
//	Given c ? camera(201, 101, ? / 2)
//	When r ? ray_for_pixel(c, 0, 0)
//	Then r.origin = point(0, 0, 0)
//	And r.direction = vector(0.66519, 0.33259, -0.66851)

//Scenario: Constructing a ray when the camera is transformed
//	Given c ? camera(201, 101, ? / 2)
//	When c.transform ? rotation_y(? / 4) * translation(0, -2, 5)
//	And r ? ray_for_pixel(c, 100, 50)
//	Then r.origin = point(0, 2, -5)
//	And r.direction = vector(?2 / 2, 0, -?2 / 2)
	void test_camera();

//Scenario: Rendering a world with a camera
//	Given w ? default_world()
//	And c ? camera(11, 11, ? / 2)
//	And from ? point(0, 0, -5)
//	And to ? point(0, 0, 0)
//	And up ? vector(0, 1, 0)
//	And c.transform ? view_transform(from, to, up)
//	When image ? render(c, w)
//	Then pixel_at(image, 5, 5) = color(0.38066, 0.47583, 0.2855)
	void test_camera_render();

	void test_world_intersections();
}

#endif
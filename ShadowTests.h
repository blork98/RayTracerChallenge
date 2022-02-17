#ifndef SHADOW_TESTS_H_
#define sHADOW_TESTS_H_

void shadow_tests();

//Scenario: Lighting with the surface in shadow
//	Given eyev ? vector(0, 0, -1)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 0, -10), color(1, 1, 1))
//	And in_shadow ? true
//	When result ? lighting(m, light, position, eyev, normalv, in_shadow)
//	Then result = color(0.1, 0.1, 0.1)

//Scenario: There is no shadow when nothing is collinear with point and light
//	Given w ? default_world()
//	And p ? point(0, 10, 0)
//	Then is_shadowed(w, p) is false

//Scenario: The shadow when an object is between the point and the light
//	Given w ? default_world()
//	And p ? point(10, -10, 10)
//	Then is_shadowed(w, p) is true

//Scenario: There is no shadow when an object is behind the light
//	Given w ? default_world()
//	And p ? point(-20, 20, -20)
//	Then is_shadowed(w, p) is false

//Scenario: There is no shadow when an object is behind the point
//	Given w ? default_world()
//	And p ? point(-2, 2, -2)
//	Then is_shadowed(w, p) is false

void test_shadows();

//Scenario: The hit should offset the point
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And shape ? sphere() with :
//	| transform | translation(0, 0, 1) |
//	And i ? intersection(5, shape)
//	When comps ? prepare_computations(i, r)
//	Then comps.over_point.z < -EPSILON / 2
//	And comps.point.z > comps.over_point.z

void test_over_point();

//Scenario: shade_hit() is given an intersection in shadow
//	Given w ? world()
//	And w.light ? point_light(point(0, 0, -10), color(1, 1, 1))
//	And s1 ? sphere()
//	And s1 is added to w
//	And s2 ? sphere() with :
//	| transform | translation(0, 0, 10) |
//	And s2 is added to w
//	And r ? ray(point(0, 0, 5), vector(0, 0, 1))
//	And i ? intersection(4, s2)
//	When comps ? prepare_computations(i, r)
//	And c ? shade_hit(w, comps)
//	Then c = color(0.1, 0.1, 0.1)

void test_shade_hit();
#endif
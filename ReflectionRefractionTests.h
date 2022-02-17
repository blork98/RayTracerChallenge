#ifndef REFLECTIONREFRACTIONTESTS_H_
#define REFLECTIONREFRACTIONTESTS_H_

void reflection_refraction_tests();

//Scenario: Reflectivity for the default material
//	Given m ? material()
//	Then m.reflective = 0.0

//Scenario: Precomputing the reflection vector
//	2 Given shape ? plane()
//	3 And r ? ray(point(0, 1, -1), vector(0, -?2 / 2, ?2 / 2))
//	4 And i ? intersection(?2, shape)
//	5 When comps ? prepare_computations(i, r)
//	6 Then comps.reflectv = vector(0, ?2 / 2, ?2 / 2)

void test_reflection_mat();

//Scenario: The reflected color for a nonreflective material
//	Given w ? default_world()
//	And r ? ray(point(0, 0, 0), vector(0, 0, 1))
//	And shape ? the second object in w
//	And shape.material.ambient ? 1
//	And i ? intersection(1, shape)
//	When comps ? prepare_computations(i, r)
//	And color ? reflected_color(w, comps)
//	Then color = color(0, 0, 0)
void test_reflective_surface_hit();

//Scenario: color_at() with mutually reflective surfaces
//	Given w ? world()
//	And w.light ? point_light(point(0, 0, 0), color(1, 1, 1))
//	And lower ? plane() with :
//	| material.reflective | 1 |
//	| transform | translation(0, -1, 0) |
//	And lower is added to w
//	And upper ? plane() with :
//	| material.reflective | 1 |
//	| transform | translation(0, 1, 0) |
//	And upper is added to w
//	And r ? ray(point(0, 0, 0), vector(0, 1, 0))
//	Then color_at(w, r) should terminate successfully
void test_infinite_recursion();

//Scenario: The reflected color at the maximum recursive depth
//	- Given w ? default_world()
//	- And shape ? plane() with :
//	-| material.reflective | 0.5 |
//	5 | transform | translation(0, -1, 0) |
//	-And shape is added to w
//	- And r ? ray(point(0, 0, -3), vector(0, -?2 / 2, ?2 / 2))
//	- And i ? intersection(?2, shape)
//	- When comps ? prepare_computations(i, r)
//	10 And color ? reflected_color(w, comps, 0)
//	- Then color = color(0, 0, 0)

void test_limit_recursion();

//Scenario Outline : Finding n1 and n2 at various intersections
// Given A ? glass_sphere() with :
//	-| transform | scaling(2, 2, 2) |
//	-| material.refractive_index | 1.5 |
//	5 And B ? glass_sphere() with :
//	-| transform | translation(0, 0, -0.25) |
//	-| material.refractive_index | 2.0 |
//	-And C ? glass_sphere() with :
//	-| transform | translation(0, 0, 0.25) |
//	10 | material.refractive_index | 2.5 |
//	-And r ? ray(point(0, 0, -4), vector(0, 0, 1))
//	- And xs ? intersections(2:A, 2.75 : B, 3.25 : C, 4.75 : B, 5.25 : C, 6 : A)
//	- When comps ? prepare_computations(xs[<index>], r, xs)
//	- Then comps.n1 = <n1>
//	15 And comps.n2 = <n2>
//	-
//	-Examples:
//-| index | n1 | n2 |
//-| 0 | 1.0 | 1.5 |
//20 | 1 | 1.5 | 2.0 |
//-| 2 | 2.0 | 2.5 |
//-| 3 | 2.5 | 2.5 |
//-| 4 | 2.5 | 1.5 |
//-| 5 | 1.5 | 1.0 |
void test_refraction_index();

//Scenario: The refracted color with an opaque surface
//	Given w ? default_world()
//	And shape ? the first object in w
//	And r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And xs ? intersections(4:shape, 6 : shape)
//	When comps ? prepare_computations(xs[0], r, xs)
//	And c ? refracted_color(w, comps, 5)
//	Then c = color(0, 0, 0)

//Scenario: The refracted color at the maximum recursive depth
//	Given w ? default_world()
//	And shape ? the first object in w
//	And shape has :
//		  | material.transparency | 1.0 |
//			  | material.refractive_index | 1.5 |
//			  And r ? ray(point(0, 0, -5), vector(0, 0, 1))
//			  And xs ? intersections(4:shape, 6 : shape)
//			  When comps ? prepare_computations(xs[0], r, xs)
//			  And c ? refracted_color(w, comps, 0)
//			  Then c = color(0, 0, 0)

//Scenario: The refracted color under total internal reflection
//	Given w ? default_world()
//	And shape ? the first object in w
//	And shape has :
//		  | material.transparency | 1.0 |
//			  | material.refractive_index | 1.5 |
//			  And r ? ray(point(0, 0, ?2 / 2), vector(0, 1, 0))
//			  And xs ? intersections(-?2 / 2:shape, ?2 / 2 : shape)
//			  # NOTE : this time you're inside the sphere, so you need
//			  # to look at the second intersection, xs[1], not xs[0]
//			  When comps ? prepare_computations(xs[1], r, xs)
//			  And c ? refracted_color(w, comps, 5)
//			  Then c = color(0, 0, 0)

void test_refracted_color();

//Scenario: The refracted color with a refracted ray
//	Given w ? default_world()
//	And A ? the first object in w
//	And A has :
//		  | material.ambient | 1.0 |
//			  | material.pattern | test_pattern() |
//			  And B ? the second object in w
//			  And B has :
//		  | material.transparency | 1.0 |
//			  | material.refractive_index | 1.5 |
//			  And r ? ray(point(0, 0, 0.1), vector(0, 1, 0))
//			  And xs ? intersections(-0.9899:A, -0.4899 : B, 0.4899 : B, 0.9899 : A)
//			  When comps ? prepare_computations(xs[2], r, xs)
//			  And c ? refracted_color(w, comps, 5)
//			  Then c = color(0, 0.99888, 0.04725)

void test_refracted_color_f();

//Scenario: shade_hit() with a transparent material
//	Given w ? default_world()
//	And floor ? plane() with :
//	| transform | translation(0, -1, 0) |
//	| material.transparency | 0.5 |
//	| material.refractive_index | 1.5 |
//	And floor is added to w
//	And ball ? sphere() with :
//	| material.color | (1, 0, 0) |
//	| material.ambient | 0.5 |
//	| transform | translation(0, -3.5, -0.5) |
//	And ball is added to w
//	And r ? ray(point(0, 0, -3), vector(0, -?2 / 2, ?2 / 2))
//	And xs ? intersections(?2:floor)
//	When comps ? prepare_computations(xs[0], r, xs)
//	And color ? shade_hit(w, comps, 5)
//	Then color = color(0.93642, 0.68642, 0.68642)

void test_refracted_shade_hit();

//Scenario: The Schlick approximation under total internal reflection
//	Given shape ? glass_sphere()
//	And r ? ray(point(0, 0, ?2 / 2), vector(0, 1, 0))
//	And xs ? intersections(-?2 / 2:shape, ?2 / 2 : shape)
//	When comps ? prepare_computations(xs[1], r, xs)
//	And reflectance ? schlick(comps)
//	Then reflectance = 1.0

//Scenario: The Schlick approximation with a perpendicular viewing angle
//	Given shape ? glass_sphere()
//	And r ? ray(point(0, 0, 0), vector(0, 1, 0))
//	And xs ? intersections(-1:shape, 1 : shape)
//	When comps ? prepare_computations(xs[1], r, xs)
//	And reflectance ? schlick(comps)
//	Then reflectance = 0.04

//Scenario: The Schlick approximation with small angle and n2 > n1
//	Given shape ? glass_sphere()
//	And r ? ray(point(0, 0.99, -2), vector(0, 0, 1))
//	And xs ? intersections(1.8589:shape)
//	When comps ? prepare_computations(xs[0], r, xs)
//	And reflectance ? schlick(comps)
//	Then reflectance = 0.48873

void test_fresnel();

//Scenario: shade_hit() with a reflective, transparent material
//	Given w ? default_world()
//	And r ? ray(point(0, 0, -3), vector(0, -?2 / 2, ?2 / 2))
//	And floor ? plane() with :
//	| transform | translation(0, -1, 0) |
//	| material.reflective | 0.5 |
//	| material.transparency | 0.5 |
//	| material.refractive_index | 1.5 |
//	And floor is added to w
//	And ball ? sphere() with:
//		  | material.color | (1, 0, 0) |
//			  | material.ambient | 0.5 |
//			  | transform | translation(0, -3.5, -0.5) |
//			  And ball is added to w
//			  And xs ? intersections(?2 : floor)
//			  When comps ? prepare_computations(xs[0], r, xs)
//			  And color ? shade_hit(w, comps, 5)
//			  Then color = color(0.93391, 0.69643, 0.69243)
void test_fresnel_shade_hit();	

#endif
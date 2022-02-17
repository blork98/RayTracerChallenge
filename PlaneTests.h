#ifndef PLANETESTS_H_
#define PLANETESTS_H_

void plane_tests();

//Scenario: Intersecting a scaled shape with a ray
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And s ? test_shape()
//	When set_transform(s, scaling(2, 2, 2))
//	And xs ? intersect(s, r)
//	Then s.saved_ray.origin = point(0, 0, -2.5)
//	And s.saved_ray.direction = vector(0, 0, 0.5)
//Scenario: Intersecting a translated shape with a ray
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And s ? test_shape()
//	When set_transform(s, translation(5, 0, 0))
//	And xs ? intersect(s, r)
//	Then s.saved_ray.origin = point(-5, 0, -5)
//	And s.saved_ray.direction = vector(0, 0, 1)

void test_local_ray();

//Scenario: Computing the normal on a translated shape
//	Given s ? test_shape()
//	When set_transform(s, translation(0, 1, 0))
//	And n ? normal_at(s, point(0, 1.70711, -0.70711))
//	Then n = vector(0, 0.70711, -0.70711)
//Scenario : Computing the normal on a transformed shape
//	Given s ? test_shape()
//	And m ? scaling(1, 0.5, 1) * rotation_z(? / 5)
//	When set_transform(s, m)
//	And n ? normal_at(s, point(0, ?2 / 2, -?2 / 2))
//	Then n = vector(0, 0.97014, -0.24254)

void test_local_normal();

//Scenario: The normal of a plane is constant everywhere
//	Given p ? plane()
//	When n1 ? local_normal_at(p, point(0, 0, 0))
//	And n2 ? local_normal_at(p, point(10, 0, -10))
//	And n3 ? local_normal_at(p, point(-5, 0, 150))
//	Then n1 = vector(0, 1, 0)
//	And n2 = vector(0, 1, 0)
//	And n3 = vector(0, 1, 0)

//Scenario: Intersect with a ray parallel to the plane
//	Given p ? plane()
//	And r ? ray(point(0, 10, 0), vector(0, 0, 1))
//	When xs ? local_intersect(p, r)
//	Then xs is empty
//	Scenario : Intersect with a coplanar ray
//	Given p ? plane()
//	And r ? ray(point(0, 0, 0), vector(0, 0, 1))
//	When xs ? local_intersect(p, r)
//	Then xs is empty

//Scenario: A ray intersecting a plane from above
//	Given p ? plane()
//	And r ? ray(point(0, 1, 0), vector(0, -1, 0))
//	When xs ? local_intersect(p, r)
//	Then xs.count = 1
//	And xs[0].t = 1
//	And xs[0].object = p
//Scenario : A ray intersecting a plane from below
//	Given p ? plane()
//	And r ? ray(point(0, -1, 0), vector(0, 1, 0))
//	When xs ? local_intersect(p, r)
//	Then xs.count = 1
//	And xs[0].t = 1
//	And xs[0].object = p

void test_plane();

#endif
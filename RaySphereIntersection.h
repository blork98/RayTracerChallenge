#ifndef RAYSPHEREINTERSECTIONS_H_
#define RAYSPHEREINTERSECTIONS_H_

void ray_sphere_intersection_tests();

//Scenario: Creating and querying a ray
//	Given origin ? point(1, 2, 3)
//	And direction ? vector(4, 5, 6)
//	When r ? ray(origin, direction)
//	Then r.origin = origin
//	And r.direction = direction

//Scenario: Computing a point from a distance
//	Given r ? ray(point(2, 3, 4), vector(1, 0, 0))
//	Then position(r, 0) = point(2, 3, 4)
//	And position(r, 1) = point(3, 3, 4)
//	And position(r, -1) = point(1, 3, 4)
//	And position(r, 2.5) = point(4.5, 3, 4)

void test_ray();

//Scenario: A ray intersects a sphere at two points
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 2
//	And xs[0] = 4.0
//	And xs[1] = 6.0

//Scenario: A ray intersects a sphere at a tangent
//	Given r ? ray(point(0, 1, -5), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 2
//	And xs[0] = 5.0
//	And xs[1] = 5.0

//Scenario: A ray misses a sphere
//	Given r ? ray(point(0, 2, -5), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 0

//Scenario: A ray originates inside a sphere
//	Given r ? ray(point(0, 0, 0), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 2
//	And xs[0] = -1.0
//	And xs[1] = 1.0

//Scenario: A sphere is behind a ray
//	Given r ? ray(point(0, 0, 5), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 2
//	And xs[0] = -6.0
//	And xs[1] = -4.0

//Scenario: Aggregating intersections
//	Given s ? sphere()
//	And i1 ? intersection(1, s)
//	And i2 ? intersection(2, s)
//	When xs ? intersections(i1, i2)
//	Then xs.count = 2
//	And xs[0].t = 1
//	And xs[1].t = 2

//Scenario: Intersect sets the object on the intersection
//	Given r ? ray(point(0, 0, -5), vector(0, 0, 1))
//	And s ? sphere()
//	When xs ? intersect(s, r)
//	Then xs.count = 2
//	And xs[0].object = s
//	And xs[1].object = s

void test_intersection();

//Scenario: Translating a ray
//	Given r ? ray(point(1, 2, 3), vector(0, 1, 0))
//	And m ? translation(3, 4, 5)
//	When r2 ? transform(r, m)
//	Then r2.origin = point(4, 6, 8)
//	And r2.direction = vector(0, 1, 0)
//Scenario : Scaling a ray
//	Given r ? ray(point(1, 2, 3), vector(0, 1, 0))
//	And m ? scaling(2, 3, 4)
//	When r2 ? transform(r, m)
//	Then r2.origin = point(2, 6, 12)
//	And r2.direction = vector(0, 3, 0)

void test_ray_object_transforms();
#endif
#ifndef TUPLETESTS_H_
#define TUPLETESTS_H_

void tuple_tests();

// Scenario: A tuple with w=1.0 is a point
//		Given a ? tuple(4.3, -4.2, 3.1, 1.0)
//		Then a.x = 4.3
//		And a.y = -4.2
//		And a.z = 3.1
//		And a.w = 1.0
//		And a is a point
//		And a is not a vector

void tuple_test_1();

//Scenario: A tuple with w = 0 is a vector
//		Given a ? tuple(4.3, -4.2, 3.1, 0.0)
//		Then a.x = 4.3
//		And a.y = -4.2
//		And a.z = 3.1
//		And a.w = 0.0
//		And a is not a point
//		And a is a vector

void tuple_test_2();

//Scenario: point() creates tuples with w = 1
//	Given p ? point(4, -4, 3)
//	Then p = tuple(4, -4, 3, 1)

void test_create_point();

//Scenario: vector() creates tuples with w = 0
//	Given v ? vector(4, -4, 3)
//	Then v = tuple(4, -4, 3, 0)

void test_create_vector();

//Scenario: Multiplying a tuple by a scalar
//	Given a ? tuple(1, -2, 3, -4)
//	Then a * 3.5 = tuple(3.5, -7, 10.5, -14)

void test_tuple_scalar_mult();

//Scenario: Dividing a tuple by a scalar
//	Given a ? tuple(1, -2, 3, -4)
//	Then a / 2 = tuple(0.5, -1, 1.5, -2)

void test_tuple_scalar_div();

//Scenario: Computing the magnitude of vector(1, 0, 0)
//
//	Given v ? vector(1, 0, 0)
//	Then magnitude(v) = 1
//	Scenario : Computing the magnitude of vector(0, 1, 0)
//	Given v ? vector(0, 1, 0)
//	Then magnitude(v) = 1
//	Scenario : Computing the magnitude of vector(0, 0, 1)
//	Given v ? vector(0, 0, 1)
//	Then magnitude(v) = 1
//	Scenario : Computing the magnitude of vector(1, 2, 3)
//	Given v ? vector(1, 2, 3)
//	Then magnitude(v) = ?14
//	Scenario : Computing the magnitude of vector(-1, -2, -3)
//	Given v ? vector(-1, -2, -3)
//	Then magnitude(v) = ?14

void test_vector_magnitude();

//Scenario: Normalizing vector(4, 0, 0) gives(1, 0, 0)
//	Given v ? vector(4, 0, 0)
//	Then normalize(v) = vector(1, 0, 0)

//Scenario: Normalizing vector(1, 2, 3)
//	Given v ? vector(1, 2, 3)
//	# vector(1 / ?14, 2 / ?14, 3 / ?14)
//	Then normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)

//Scenario: The magnitude of a normalized vector
//	Given v ? vector(1, 2, 3)
//	When norm ? normalize(v)
//	Then magnitude(norm) = 1

void test_normalized_vector1();

//Scenario: The dot product of two tuples
//	Given a ? vector(1, 2, 3)
//	And b ? vector(2, 3, 4)
//	Then dot(a, b) = 20

void test_dot_product();

//Scenario: The cross product of two vectors
//	Given a ? vector(1, 2, 3)
//	And b ? vector(2, 3, 4)
//	Then cross(a, b) = vector(-1, 2, -1)
//	And cross(b, a) = vector(1, -2, 1)

void test_cross_product();

//Scenario: Adding two tuples
//	Given a1 ? tuple(3, -2, 5, 1)
//	And a2 ? tuple(-2, 3, 1, 0)
//	Then a1 + a2 = tuple(1, 1, 6, 1)

//Scenario: Subtracting two points
//	Given p1 ? point(3, 2, 1)
//	And p2 ? point(5, 6, 7)
//	Then p1 - p2 = vector(-2, -4, -6)

//Scenario: Subtracting a vector from a point
//	Given p ? point(3, 2, 1)
//	And v ? vector(5, 6, 7)
//	Then p - v = point(-2, -4, -6)
	
void test_tuple_add_sub();

#endif
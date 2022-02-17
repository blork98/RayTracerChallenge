#include "TupleTests.h"
#include "Tuple.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

using namespace RTC;

void tuple_tests()
{
	std::cout << "Tuple Tests:" << std::endl << std::endl;

	tuple_test_1();
	tuple_test_2();
	test_create_point();
	test_create_vector();
	test_tuple_scalar_mult();
	test_tuple_scalar_div();
	test_vector_magnitude();
	test_normalized_vector1();
	test_dot_product();
	test_cross_product();
	test_tuple_add_sub();

	std::cout << std::endl << std::endl;
}

void test_tuple_add_sub()
{
	std::cout << "Test Tuple Addition and Subtraction" << std::endl << std::endl;

	//Test Addition
	Tuple a(3.0f, -2.0f, 5.0f, 1.0f);
	Tuple b(-2.0f,3.0f,1.0f,0.0f);
	Tuple c = a + b;

	//Test Addition
	if (essentially_equal(1.0f, c.x) && essentially_equal(1.0f, c.y) && essentially_equal(6.0f, c.z)&&essentially_equal(1.0f,c.w))
		std::cout << "T(3,-2,5,1) + T(-2,3,1,0) is T(1,1,6,1): Test Passed" << std::endl;

	//Test Point - Point
	Tuple p1 = create_tuple_point(3.0f, 2.0f, 1.0f);
	Tuple p2 = create_tuple_point(5.0f, 6.0f, 7.0f);
	Tuple v1 = p1 - p2;

	if (essentially_equal(-2.0f, v1.x) && essentially_equal(-4.0f, v1.y) && essentially_equal(-6.0f, v1.z) && essentially_equal(0.0f, v1.w))
		std::cout << "P(3,2,1) - P(5,6,7) is V(-2,-4,-6): Test Passed" << std::endl;

	//Test Point - Vector
	Tuple v = create_tuple_vector(5.0f, 6.0f, 7.0f);
	Tuple p = p1 - v;

	if (essentially_equal(-2.0f, p.x) && essentially_equal(-4.0f, p.y) && essentially_equal(-6.0f, p.z) && essentially_equal(1.0f, p.w))
		std::cout << "P(3,2,1) - V(5,6,7) is P(-2,-4,-6): Test Passed" << std::endl;

	std::cout << std::endl;
}

void test_cross_product()
{
	std::cout << "Test cross Product" << std::endl << std::endl;

	Tuple a = create_tuple_vector(1.0f,2.0f,3.0f);
	Tuple b = create_tuple_vector(2.0f, 3.0f, 4.0f);
	Tuple c = vector_cross_product(a, b);
	Tuple d = vector_cross_product(b, a);

	//Test axb
	if (essentially_equal(-1.0f, c.x) && essentially_equal(2.0f, c.y) && essentially_equal(-1.0f, c.z))
		std::cout << "V(1,2,3) X V(2,3,4) is V(-1,2,-1): Test Passed" << std::endl;
	else
		std::cout << "V(1,2,3) X V(2,3,4) is not V(-1,2,-1): Test not Passed" << std::endl;

	//Test bxa
	if (essentially_equal(1.0f, d.x) && essentially_equal(-2.0f, d.y) && essentially_equal(1.0f, d.z))
		std::cout << "V(2,3,4) x V(1,2,3) is V(1,-2,1): Test Passed" << std::endl;
	else
		std::cout << "V(2,3,4) x V(1,2,3) is not V(1,-2,1): Test not Passed" << std::endl;

	std::cout << std::endl;
}

void test_dot_product()
{
	std::cout << "Test Dot Product" << std::endl << std::endl;

	Tuple a = create_tuple_vector(1.0f,2.0f,3.0f);
	Tuple b = create_tuple_vector(2.0f, 3.0f, 4.0f);

	if (essentially_equal(20.0f, vector_dot_product(a, b)))
		std::cout << "Dot product of Vector(1,2,3) and Vector(2,3,4) is 20: Test passed" << std::endl;
	else
		std::cout << "Dot product of Vector(1,2,3) and Vector(2,3,4) is not 20: Test not passed" << std::endl;

	std::cout<<std::endl;
}


void test_normalized_vector1()
{
	std::cout << "Test Vector Normalization" << std::endl << std::endl;

	//Test V(4,0,0)
	Tuple a(4.0f,0.0f,0.0f,0.0f);
	Tuple b = normalize_vector(a);

	if (essentially_equal(1.0f, b.x) && essentially_equal(0.0f, b.y) && essentially_equal(0.0f, b.z))
		std::cout << " Normalizing Vector(4,0,0) results in Vector(1,0,0): Test passed " << std::endl;
	else
		std::cout << " Normalizing Vector(4,0,0) does not result in Vector(1,0,0): Test not passed " << std::endl;

	//Test V(1,2,3)
	Tuple c(1.0f, 2.0f, 3.0f,0.0f);
	Tuple d = normalize_vector(c);
	float mag = vector_magnitude(c);

	if (essentially_equal(1.0f/mag, d.x) && essentially_equal(2.0f/mag, d.y) && essentially_equal(3.0f/mag, d.z))
		std::cout << " Normalizing Vector(1,2,3) results in Vector(1/sqrt(14),2/sqrt(14),3/sqrt(14)): Test passed " << std::endl;
	else
		std::cout << " Normalizing Vector(1,2,3) does not result in Vector(1/sqrt(14),2/sqrt(14),3/sqrt(14)): Test not passed " << std::endl;

	//Magnitude Test
	if (essentially_equal(vector_magnitude(d), 1.0f))
		std::cout << " Magnitude of Normalized Vector(1,2,3) is 1: Test passed" << std::endl;
	else
		std::cout << " Magnitude of Normalized Vector(1,2,3) is not 1: Test not passed" << std::endl;

	std::cout << std::endl;
}

void test_vector_magnitude()
{
	std::cout << "Test Vector Magnitude" << std::endl << std::endl;

	Tuple a = create_tuple_vector(0.0f,1.0f,0.0f);

	if (essentially_equal(vector_magnitude(a), 1.0f))
		std::cout << "Vector(0,1,0) has magnitude 1.0: Test passed" << std::endl;
	else
		std::cout << "Vector(0,1,0) does not have magnitude 1.0: Test failed" << std::endl;

	a = create_tuple_vector(1.0f, 0.0f, 0.0f);

	if (essentially_equal(vector_magnitude(a), 1.0f))
		std::cout << "Vector(1,0,0) has magnitude 1.0: Test passed" << std::endl;
	else
		std::cout << "Vector(1,0,0) does not have magnitude 1.0: Test failed" << std::endl;

	a = create_tuple_vector(0.0f, 0.0f, 1.0f);

	if (essentially_equal(vector_magnitude(a), 1.0f))
		std::cout << "Vector(0,0,1) has magnitude 1.0: Test passed" << std::endl;
	else
		std::cout << "Vector(0,0,1) does not have magnitude 1.0: Test failed" << std::endl;

	a = create_tuple_vector(1.0f, 2.0f, 3.0f);

	if (essentially_equal(vector_magnitude(a), std::sqrtf(14)))
		std::cout << "Vector(1,2,3) has magnitude sqrt(14): Test passed" << std::endl;
	else
		std::cout << "Vector(1,2,3) does not have magnitude sqrt(14): Test failed" << std::endl;

	a = create_tuple_vector(-1.0f, -2.0f, -3.0f);

	if (essentially_equal(vector_magnitude(a), std::sqrtf(14)))
		std::cout << "Vector(-1,-2,-3) has magnitude sqrt(14): Test passed" << std::endl;
	else
		std::cout << "Vector(-1,-2,-3) does not have magnitude sqrt(14): Test failed" << std::endl;
	std::cout << std::endl;
}

void test_tuple_scalar_div()
{
	std::cout << "Test Tuple Scalar Division" << std::endl;

	Tuple a(1.0f, -2.0f, 3.0f, -4.0f);
	Tuple b = a / 2.0f;

	if (essentially_equal(0.5f, b.x))
	{
		std::cout << "B.x = 0.5 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.x != 0.5 : Test failed" << std::endl;
	}

	if (essentially_equal(-1.0f, b.y))
	{
		std::cout << "B.y = -1.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.y != -1.0 : Test failed" << std::endl;
	}

	if (essentially_equal(1.5f, b.z))
	{
		std::cout << "B.z = 1.5 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.z != 1.5 : Test failed" << std::endl;
	}

	if (essentially_equal(-2.0f, b.w))
	{
		std::cout << "B.w = -2.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.w != -2.0 : Test failed" << std::endl;
	}

	std::cout << std::endl;
}

void test_tuple_scalar_mult()
{
	std::cout << "Test Tuple Scalar Multiplication" << std::endl;

	Tuple a(1.0f, -2.0f, 3.0f, -4.0f);

	Tuple b = a*3.5;
	Tuple c = 3.5*a;

	if (essentially_equal(3.5f, b.x))
	{
		std::cout << "B.x = 3.5 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.x != 3.5 : Test failed" << std::endl;
	}

	if (essentially_equal(-7.0f, b.y))
	{
		std::cout << "B.y = -7.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.y != -7.0 : Test failed" << std::endl;
	}

	if (essentially_equal(10.5f, b.z))
	{
		std::cout << "B.z = 10.5 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.z != 10.5 : Test failed" << std::endl;
	}

	if (essentially_equal(-14.0f, b.w))
	{
		std::cout << "B.w = -14.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "B.w != -14.0 : Test failed" << std::endl;
	}

	std::cout << std::endl;
}

void test_create_vector()
{
	std::cout << "Test Create Vector" << std::endl;

	Tuple a = create_tuple_vector(4.0f, -4.0f, 3.0f);

	if (essentially_equal(4.0f, a.x))
	{
		std::cout << "A.x = 4.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.x != 4.0 : Test failed" << std::endl;
	}

	if (essentially_equal(-4.0f, a.y))
	{
		std::cout << "A.y = -4.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.y != -4.0 : Test failed" << std::endl;
	}

	if (essentially_equal(3.0f, a.z))
	{
		std::cout << "A.z = 3.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.z != 3.0 : Test failed" << std::endl;
	}

	if (essentially_equal(0.0f, a.w))
	{
		std::cout << "A.w = 0.0 : Test passed" << std::endl;
		std::cout << "A is not a point. A is a vector : Test passed" << std::endl;
	}
	else {
		std::cout << "A.w != 1.0 : Test failed" << std::endl;
		std::cout << "A is not a vector : Test failed" << std::endl;
	}

	std::cout << std::endl;
}

void test_create_point()
{
	std::cout << "Test Create Point" << std::endl;

	Tuple a = create_tuple_point(4.0f,-4.0f,3.0f);

	if (essentially_equal(4.0f, a.x))
	{
		std::cout << "A.x = 4.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.x != 4.0 : Test failed" << std::endl;
	}

	if (essentially_equal(-4.0f, a.y))
	{
		std::cout << "A.y = -4.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.y != -4.0 : Test failed" << std::endl;
	}

	if (essentially_equal(3.0f, a.z))
	{
		std::cout << "A.z = 3.0 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.z != 3.0 : Test failed" << std::endl;
	}

	if (essentially_equal(1.0f, a.w))
	{
		std::cout << "A.w = 1.0 : Test passed" << std::endl;
		std::cout << "A is a point. A is not a vector : Test passed" << std::endl;
	}
	else {
		std::cout << "A.w != 1.0 : Test failed" << std::endl;
		std::cout << "A is not a point : Test failed" << std::endl;
	}
	std::cout << std::endl;
}

void tuple_test_1()
{
	std::cout << "Test Tuple 1" << std::endl;

	Tuple a(4.3f,-4.2f,3.1f,1.0f);

	if (essentially_equal(4.3f, a.x))
	{
		std::cout << "A.x = 4.3 : Test passed" << std::endl;
	} else {
		std::cout << "A.x != 4.3 : Test failed" << std::endl;
	}

	if (essentially_equal(-4.2f, a.y))
	{
		std::cout << "A.y = -4.2 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.y != -4.2 : Test failed" << std::endl;
	}

	if (essentially_equal(3.1f, a.z))
	{
		std::cout << "A.z = 3.1 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.z != 3.1 : Test failed" << std::endl;
	}

	if (essentially_equal(1.0f, a.w))
	{
		std::cout << "A.w = 1.0 : Test passed" << std::endl;
		std::cout << "A is a point. A is not a vector : Test passed" << std::endl;
	}
	else {
		std::cout << "A.w != 1.0 : Test failed" << std::endl;
		std::cout << "A is not a point : Test failed" << std::endl;
	}

	std::cout << std::endl;
}

void tuple_test_2()
{
	std::cout << "Test Tuple 2" << std::endl;

	Tuple a(4.3f, -4.2f, 3.1f, 0.0f);

	if (essentially_equal(4.3f, a.x))
	{
		std::cout << "A.x = 4.3 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.x != 4.3 : Test failed" << std::endl;
	}

	if (essentially_equal(-4.2f, a.y))
	{
		std::cout << "A.y = -4.2 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.y != -4.2 : Test failed" << std::endl;
	}

	if (essentially_equal(3.1f, a.z))
	{
		std::cout << "A.z = 3.1 : Test passed" << std::endl;
	}
	else {
		std::cout << "A.z != 3.1 : Test failed" << std::endl;
	}

	if (essentially_equal(0.0f, a.w))
	{
		std::cout << "A.w = 0.0 : Test passed" << std::endl;
		std::cout << "A is not a point. A is a vector : Test passed" << std::endl;
	}
	else {
		std::cout << "A.w != 1.0 : Test failed" << std::endl;
		std::cout << "A is not a vector : Test failed" << std::endl;
	}
	std::cout << std::endl;
}

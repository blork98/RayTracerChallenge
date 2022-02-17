#include "Constants.h"
#include "TransformTests.h"
#include "Transform.h"
#include <iostream>

using namespace RTC;

void transform_tests()
{
	std::cout << "Transform Tests:" << std::endl << std::endl;

	test_transform_class();
	translation_tests();
	scaling_tests();
	rotation_tests();
	shearing_test();
	compound_transform_test();

	std::cout << std::endl << std::endl;
}

void test_transform_class()
{
	Translation trans1;
	Translation trans2(2.0, 3.0, 4.0);
	Translation trans3 = trans2;
	trans1 = trans3;
}

void compound_transform_test()
{
	std::cout << "Test Chained Transform" << std::endl << std::endl;

	//Individual Transform
	Tuple point1 = create_tuple_point(1.0f, 0.0f, 1.0f);
	Rotation A;
	A.rotate_x(M_PI_2);
	Scaling B(5.0f, 5.0f, 5.0f);
	Translation C(10.0f,5.0f,7.0f);

	Tuple point2 = A.apply_transform(point1);
	point2 = B.apply_transform(point2);
	point2 = C.apply_transform(point2);

	bool test1 = essentially_equal(15.0f, point2.x) && essentially_equal(0.0f, point2.y) && essentially_equal(7.0f, point2.z);

	if (test1)
		std::cout << " Test Transforms Applied in Sequence: Test Passed" << std::endl;
	else
		std::cout << " Test Transforms Applied in Sequence: Test Failed" << std::endl;
	std::cout << std::endl;

	//Compount Transform
	point2 = create_tuple_point(0.0f, 0.0f, 0.0f);
	std::vector<std::shared_ptr<Transform>> transforms;
	transforms.push_back(std::make_shared<Transform>(A));
	transforms.push_back(std::make_shared<Transform>(B));
	transforms.push_back(std::make_shared<Transform>(C));
	CompoundTransform combTransform(transforms);
	point2 = combTransform.apply_transform(point1);
	test1 = essentially_equal(15.0f, point2.x) && essentially_equal(0.0f, point2.y) && essentially_equal(7.0f, point2.z);

	if (test1)
		std::cout << " Test Compound Transforms: Test Passed" << std::endl;
	else
		std::cout << " Test Compund Transforms: Test Failed" << std::endl;
	std::cout << std::endl;

}

void shearing_test()
{
	std::cout << "Test Shearing" << std::endl << std::endl;

	Shearing trans1(1.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
	Tuple point1 = create_tuple_point(2.0f,3.0f,4.0f);
	Tuple point2 = trans1.apply_transform(point1);

	bool test1 = essentially_equal(5.0f, point2.x) && essentially_equal(3.0f, point2.y) && essentially_equal(4.0f,point2.z);

	if (test1)
		std::cout << " Test Shearing(1,0,0,0,0,0): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(1,0,0,0,0,0): Test Failed" << std::endl;

	Shearing trans2(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	point2 = trans2.apply_transform(point1);
	test1 = essentially_equal(6.0f, point2.x) && essentially_equal(3.0f, point2.y) && essentially_equal(4.0f, point2.z);

	if (test1)
		std::cout << " Test Shearing(0,1,0,0,0,0): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(0,1,0,0,0,0): Test Failed" << std::endl;

	Shearing trans3(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	point2 = trans3.apply_transform(point1);
	test1 = essentially_equal(2.0f, point2.x) && essentially_equal(5.0f, point2.y) && essentially_equal(4.0f, point2.z);

	if (test1)
		std::cout << " Test Shearing(0,0,1,0,0,0): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(0,0,1,0,0,0): Test Failed" << std::endl;

	Shearing trans4(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	point2 = trans4.apply_transform(point1);
	test1 = essentially_equal(2.0f, point2.x) && essentially_equal(7.0f, point2.y) && essentially_equal(4.0f, point2.z);

	if (test1)
		std::cout << " Test Shearing(0,0,0,1,0,0): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(0,0,0,1,0,0): Test Failed" << std::endl;

	Shearing trans5(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	point2 = trans5.apply_transform(point1);
	test1 = essentially_equal(2.0f, point2.x) && essentially_equal(3.0f, point2.y) && essentially_equal(6.0f, point2.z);

	if (test1)
		std::cout << " Test Shearing(0,0,0,0,1,0): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(0,0,0,0,1,0): Test Failed" << std::endl;

	Shearing trans6(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	point2 = trans6.apply_transform(point1);
	test1 = essentially_equal(2.0f, point2.x) && essentially_equal(3.0f, point2.y) && essentially_equal(7.0f, point2.z);

	if (test1)
		std::cout << " Test Shearing(0,0,0,0,0,1): Test Passed" << std::endl;
	else
		std::cout << " Test Shearing(0,0,0,0,0,1): Test Failed" << std::endl;

	std::cout << std::endl;
}

void rotation_tests()
{
	std::cout << "Test Rotation" << std::endl << std::endl;

	//Rotation Around x
	Rotation rotx;
	rotx.rotate_x(0.25*M_PI);
	Tuple point1 = create_tuple_point(0.0f,1.0f,0.0f);
	Tuple point2 = rotx.apply_transform(point1);
	bool test1 = floatCompareSpecified(0.0f, point2.x,0.00001) && floatCompareSpecified(0.5f*std::sqrtf(2.0f), point2.y,0.00001) && floatCompareSpecified(0.5f*std::sqrtf(2.0f), point2.z,0.00001);
	
	if(test1)
		std::cout << " Test Rotate X by Half Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate X by Half Quarter: Test Failed" << std::endl;

	rotx.rotate_x(M_PI_2);
	point2 = rotx.apply_transform(point1);
	test1 = essentially_equal(0.0f, point2.x) && absoluteToleranceCompare(0.0f, point2.y) && essentially_equal(1.0f, point2.z);

	if (test1)
		std::cout << " Test Rotate X by Full Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate X by Full Quarter: Test Failed" << std::endl;

	//Rotation aroud y
	rotx.set_to_identity();
	rotx.rotate_y(0.25*M_PI);
	point1 = create_tuple_point(0.0f, 0.0f, 1.0f);
	point2 = rotx.apply_transform(point1);
	test1 = floatCompareSpecified(0.5f*std::sqrtf(2.0f), point2.x,0.00001) && floatCompareSpecified(0.0f, point2.y,0.00001) && floatCompareSpecified(0.5f*std::sqrtf(2.0f), point2.z,0.00001);

	if (test1)
		std::cout << " Test Rotate Y by Half Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate Y by Half Quarter: Test Failed" << std::endl;

	rotx.set_to_identity();
	rotx.rotate_y(M_PI_2);
	point2 = rotx.apply_transform(point1);
	test1 = essentially_equal(1.0f, point2.x) && absoluteToleranceCompare(0.0f, point2.y) && absoluteToleranceCompare(0.0f, point2.z);

	if (test1)
		std::cout << " Test Rotate Y by Full Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate Y by Full Quarter: Test Failed" << std::endl;

	//Rotate Around Z
	rotx.set_to_identity();
	rotx.rotate_z(0.25*M_PI);
	point1 = create_tuple_point(0.0f, 1.0f, 0.0f);
	point2 = rotx.apply_transform(point1);
	test1 = floatCompareSpecified(-0.5f*std::sqrtf(2.0f), point2.x,0.00001) && floatCompareSpecified(0.5f*std::sqrtf(2.0f), point2.y,0.00001) && floatCompareSpecified(0.0, point2.z,0.00001);

	if (test1)
		std::cout << " Test Rotate Z by Half Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate Z by Half Quarter: Test Failed" << std::endl;

	rotx.set_to_identity();
	rotx.rotate_z(M_PI_2);
	point2 = rotx.apply_transform(point1);
	test1 = essentially_equal(-1.0f, point2.x) && absoluteToleranceCompare(0.0f, point2.y) && absoluteToleranceCompare(0.0f, point2.z);

	if (test1)
		std::cout << " Test Rotate Z by Full Quarter: Test Passed" << std::endl;
	else
		std::cout << " Test Rotate Z by Full Quarter: Test Failed" << std::endl;

	std::cout << std::endl;
}

void scaling_tests()
{
	std::cout << "Test Scaling" << std::endl << std::endl;

	//Scaling a Point
	Scaling transform1(2.0f,3.0f,4.0f);
	Tuple point1 = create_tuple_point(-4.0f,6.0f,8.0f);
	Tuple point2 = transform1.apply_transform(point1);

	bool test1 = essentially_equal(-8.0f, point2.x) && essentially_equal(18.0f, point2.y) && essentially_equal(32.0f, point2.z) && essentially_equal(1.0f, point2.w);

	if (test1)
		std::cout << " Test Point Scaling: Test Passed" << std::endl;
	else
		std::cout << " Test Point Scaling: Test Failed" << std::endl;

	//Scaling a vector
	point1 = create_tuple_vector(-4.0f, 6.0f, 8.0f);
	point2 = transform1.apply_transform(point1);
	test1 = essentially_equal(-8.0f, point2.x) && essentially_equal(18.0f, point2.y) && essentially_equal(32.0f, point2.z) && essentially_equal(0.0f,point2.w);

	if (test1)
		std::cout << " Test Vector Scaling: Test Passed" << std::endl;
	else
		std::cout << " Test Vector Scaling: Test Failed" << std::endl;

	//Inverse Scaling
	point2 = transform1.apply_inverse_transform(point1);
	test1 = essentially_equal(-2.0f, point2.x) && essentially_equal(2.0f, point2.y) && essentially_equal(2.0f, point2.z) && essentially_equal(0.0f, point2.w);

	if (test1)
		std::cout << " Test Vector Inverse Scaling: Test Passed" << std::endl;
	else
		std::cout << " Test Vector Inverse Scaling: Test Failed" << std::endl;

	//Test Reflection
	Scaling transform2(-1.0f,1.0f,1.0f);
	point1 = create_tuple_point(2.0f, 3.0f, 4.0f);
	point2 = transform2.apply_transform(point1);
	test1 = essentially_equal(-2.0f, point2.x) && essentially_equal(3.0f, point2.y) && essentially_equal(4.0f, point2.z) && essentially_equal(1.0f, point2.w);

	if (test1)
		std::cout << " Test Reflection Scaling: Test Passed" << std::endl;
	else
		std::cout << " Test Reflection Scaling: Test Failed" << std::endl;

	std::cout << std::endl;
}

void translation_tests()
{
	std::cout << "Test Translation" << std::endl << std::endl;

	//Test Translation
	Translation translation1(5.0f, -3.0f, 2.0f);
	Tuple point1 = create_tuple_point(-3.0f, 4.0f, 5.0f);
	Tuple point2 = translation1.apply_transform(point1);

	bool test1 = essentially_equal(point2.x, 2.0f) && essentially_equal(point2.y, 1.0f) && essentially_equal(point2.z, 7.0f);

	if (test1)
		std::cout << "Point Translation Transform: Test Passed" << std::endl;
	else
		std::cout << "Point Translation Transform: Test Filed" << std::endl;

	//Test Translation Inverse
	point2 = translation1.apply_inverse_transform(point1);
	test1 = essentially_equal(point2.x, -8.0f) && essentially_equal(point2.y, 7.0f) && essentially_equal(point2.z, 3.0f);

	if (test1)
		std::cout << "Point Translation Inverse Transform: Test Passed" << std::endl;
	else
		std::cout << "Point Translation Inverse Transform: Test Filed" << std::endl;


	//Test Vector Translation
	Tuple point3 = create_tuple_vector(-3.0,4.0f,5.0f);
	point2 = translation1.apply_transform(point3);
	test1 = essentially_equal(point2.x, -3.0f) && essentially_equal(point2.y, 4.0f) && essentially_equal(point2.z, 5.0f);

	if (test1)
		std::cout << "Vector Translation Transform: Test Passed" << std::endl;
	else
		std::cout << "Vector Translation Transform: Test Failed" << std::endl;

	std::cout << std::endl;
}
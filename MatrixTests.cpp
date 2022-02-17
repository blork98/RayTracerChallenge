#include "MatrixTests.h"

#include "Constants.h"
#include "MATRIX.h"
#include "Tuple.h"
#include <iostream>

using namespace RTC;

void matrix_tests()
{
	std::cout<<"Matrix Tests:" << std::endl << std::endl;

	test_matrix_assignment();
	test_matrix_equality();
	test_matrix_multiplication();
	test_matrix_operations();
	test_matrix_inverse();
	test_matrix_inverse2();

	std::cout << std::endl << std::endl;
}

void test_matrix_inverse2()
{
	std::cout << "Test Matrix Inverse" << std::endl;

	//Test Invertibility
	Matrix4 mat4;

	mat4.m[0][0] = 6.0f;	mat4.m[0][1] = 4.0f;	mat4.m[0][2] = 4.0f;	mat4.m[0][3] = 4.0f;
	mat4.m[1][0] = 5.0f;	mat4.m[1][1] = 5.0f;	mat4.m[1][2] = 7.0f;	mat4.m[1][3] = 6.0f;
	mat4.m[2][0] = 4.0f;	mat4.m[2][1] = -9.0f;	mat4.m[2][2] = 3.0f;	mat4.m[2][3] = -7.0f;
	mat4.m[3][0] = 9.0f;	mat4.m[3][1] = 1.0f;	mat4.m[3][2] = 7.0f;	mat4.m[3][3] = -6.0f;

	float detMat4 = det(mat4);
	bool isInvertibleMat4 = is_invertible(mat4);

	if(isInvertibleMat4)
		std::cout << "Test for Matrix Invertability: Det != 0    Test Passed" << std::endl;
	else
		std::cout << "Test for Matrix Invertability: Det != 0    Test Failed" << std::endl;

	Matrix4 mat5;

	mat5.m[0][0] = -4.0f;	mat5.m[0][1] = 2.0f;	mat5.m[0][2] = -2.0f;	mat5.m[0][3] = -3.0f;
	mat5.m[1][0] = 9.0f;	mat5.m[1][1] = 6.0f;	mat5.m[1][2] = 2.0f;	mat5.m[1][3] = 6.0f;
	mat5.m[2][0] = 0.0f;	mat5.m[2][1] = -5.0f;	mat5.m[2][2] = 1.0f;	mat5.m[2][3] = -5.0f;
	mat5.m[3][0] = 0.0f;	mat5.m[3][1] = 0.0f;	mat5.m[3][2] = 0.0f;	mat5.m[3][3] = 0.0f;

	float detMat5 = det(mat5);
	bool isInvertibleMat5 = is_invertible(mat5);

	if (!isInvertibleMat5)
		std::cout << "Test for Matrix Invertability: Det == 0    Test Passed" << std::endl;
	else
		std::cout << "Test for Matrix Invertability: Det == 0    Test Failed" << std::endl;

	//Test Inverse 1

	mat4.m[0][0] = -5.0f;	mat4.m[0][1] = 2.0f;	mat4.m[0][2] = 6.0f;	mat4.m[0][3] = -8.0f;
	mat4.m[1][0] = 1.0f;	mat4.m[1][1] = -5.0f;	mat4.m[1][2] = 1.0f;	mat4.m[1][3] = 8.0f;
	mat4.m[2][0] = 7.0f;	mat4.m[2][1] = 7.0f;	mat4.m[2][2] = -6.0f;	mat4.m[2][3] = -7.0f;
	mat4.m[3][0] = 1.0f;	mat4.m[3][1] = -3.0f;	mat4.m[3][2] = 7.0f;	mat4.m[3][3] = 4.0f;

	bool inverseTest = get_inverse(mat4, mat5);
	detMat4 = det(mat4);
	float cofMat423 = cofactor_matrix4(mat4, 2, 3);
	float cofMat432 = cofactor_matrix4(mat4, 3, 2);

	std::cout << "Calculate Matrix Inverse Test 1:" << std::endl << std::endl;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << mat5.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	//Test Inverse 2
	mat4.m[0][0] = 8.0f;	mat4.m[0][1] = -5.0f;	mat4.m[0][2] = 9.0f;	mat4.m[0][3] = 2.0f;
	mat4.m[1][0] = 7.0f;	mat4.m[1][1] = 5.0f;	mat4.m[1][2] = 6.0f;	mat4.m[1][3] = 1.0f;
	mat4.m[2][0] = -6.0f;	mat4.m[2][1] = 0.0f;	mat4.m[2][2] = 9.0f;	mat4.m[2][3] = 6.0f;
	mat4.m[3][0] = -3.0f;	mat4.m[3][1] = 0.0f;	mat4.m[3][2] = -9.0f;	mat4.m[3][3] = -4.0f;

	inverseTest = get_inverse(mat4, mat5);
	std::cout << "Calculate Matrix Inverse Test 2:" << std::endl << std::endl;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << mat5.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	//Test Inverse 3
	mat4.m[0][0] = 9.0f;	mat4.m[0][1] = 3.0f;	mat4.m[0][2] = 0.0f;	mat4.m[0][3] = 9.0f;
	mat4.m[1][0] = -5.0f;	mat4.m[1][1] = -2.0f;	mat4.m[1][2] = -6.0f;	mat4.m[1][3] = -3.0f;
	mat4.m[2][0] = -4.0f;	mat4.m[2][1] = 9.0f;	mat4.m[2][2] = 6.0f;	mat4.m[2][3] = 4.0f;
	mat4.m[3][0] = -7.0f;	mat4.m[3][1] = 6.0f;	mat4.m[3][2] = 6.0f;	mat4.m[3][3] = 2.0f;

	inverseTest = get_inverse(mat4, mat5);
	std::cout << "Calculate Matrix Inverse Test 3:" << std::endl << std::endl;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << mat5.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void test_matrix_inverse()
{
	std::cout << " Test Matrix Determinant" << std::endl;

	//Test 2x2 Determinant
	Matrix2 a;

	a.m[0][0] = 1.0f;	a.m[0][1] = 5.0f;	
	a.m[1][0] = -3.0f;	a.m[1][1] = 2.0f;

	float detA = det(a);

	if (essentially_equal(detA, 17.0f))
		std::cout << "Determinant of 2x2 Matrix Test Passed" << std::endl;
	else
		std::cout << "Determinant of 2x2 Matrix Test Failed" << std::endl;

	//Test Submatrix 2x2
	Matrix3 b;

	b.m[0][0] = 1.0f;	b.m[0][1] = 5.0f;	b.m[0][2] = 0.0f;	
	b.m[1][0] = -3.0f;	b.m[1][1] = 2.0f;	b.m[1][2] = 7.0f;	
	b.m[2][0] = 0.0f;	b.m[2][1] = 6.0f;	b.m[2][2] = -3.0f;

	a = get_submatrix2(b, 0, 2);

	bool test1 = essentially_equal(a.m[0][0], -3.0f) && essentially_equal(a.m[0][1], 2.0f) && essentially_equal(a.m[1][0], 0.0f) && essentially_equal(a.m[1][1],6.0f);

	if (test1)
		std::cout << "Get Submatrix from Matrix3 Test Passed" << std::endl;
	else
		std::cout << "Get Submatrix from Matrix3 Test Passed" << std::endl;

	//Test Submatrix 3x3
	Matrix4 mat4;

	mat4.m[0][0] = -6.0f;	mat4.m[0][1] = 1.0f;	mat4.m[0][2] = 1.0f;	mat4.m[0][3] = 6.0f;
	mat4.m[1][0] = -8.0f;	mat4.m[1][1] = 5.0f;	mat4.m[1][2] = 8.0f;	mat4.m[1][3] = 6.0f;
	mat4.m[2][0] = -1.0f;	mat4.m[2][1] = 0.0f;	mat4.m[2][2] = 8.0f;	mat4.m[2][3] = 2.0f;
	mat4.m[3][0] = -7.0f;	mat4.m[3][1] = 1.0f;	mat4.m[3][2] = -1.0f;	mat4.m[3][3] = 1.0f;

	b = get_submatrix3(mat4, 2, 1);

	test1 = essentially_equal(b.m[0][0], -6.0f) && essentially_equal(b.m[0][1], 1.0f) && essentially_equal(a.m[0][2], 6.0f) && 
			essentially_equal(b.m[1][0], -8.0f) && essentially_equal(b.m[1][1], 8.0f) && essentially_equal(a.m[1][2], 6.0f) &&
			essentially_equal(b.m[2][0], -7.0f) && essentially_equal(b.m[2][1], -1.0f) && essentially_equal(a.m[2][2], 1.0f);

	if (test1)
		std::cout << "Get Submatrix from Matrix4 Test Passed" << std::endl;
	else
		std::cout << "Get Submatrix from Matrix4 Test Passed" << std::endl;

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			std::cout << b.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	//Test Minor 3x3
	b.m[0][0] = 3.0f;	b.m[0][1] = 5.0f;	b.m[0][2] = 0.0f;
	b.m[1][0] = 2.0f;	b.m[1][1] = -1.0f;	b.m[1][2] = -7.0f;
	b.m[2][0] = 6.0f;	b.m[2][1] = -1.0f;	b.m[2][2] = 5.0f;

	float minor1 = minor_matrix3(b,1,0);

	if( essentially_equal(25.0f,minor1))
		std::cout << "Calculate Minor(0,1): Test Passed" << std::endl;
	else
		std::cout << "Calculate Minor(0,1): Test Failed" << std::endl;

	//Test minor, cofactor
	float testMinor1 = minor_matrix3(b,0,0);
	float testCofactor1 = cofactor_matrix3(b, 0, 0);

	float testMinor2 = minor_matrix3(b, 1, 0);
	float testCofactor2 = cofactor_matrix3(b, 1, 0);

	bool testCM1 = essentially_equal(-12.0f, testMinor1) && essentially_equal(-12.0f, testCofactor1);
	bool testCM2 = essentially_equal(25.0f, testMinor2) && essentially_equal(-25.0f, testCofactor2);

	if( testCM1&&testCM2)
		std::cout << "Calculate Minor and Cofactor: Test Passed" << std::endl;
	else
		std::cout << "Calculate Minor and Cofactor: Test Failed" << std::endl;

	//Test 3x3 Determinant

	b.m[0][0] = 1.0f;	b.m[0][1] = 2.0f;	b.m[0][2] = 6.0f;
	b.m[1][0] = -5.0f;	b.m[1][1] = 8.0f;	b.m[1][2] = -4.0f;
	b.m[2][0] = 2.0f;	b.m[2][1] = 6.0f;	b.m[2][2] = 4.0f;

	float testDet3 = det(b);
	float testDet3Cof0 = cofactor_matrix3(b, 0, 0);
	float testDet3Cof1 = cofactor_matrix3(b, 0, 1);
	float testDet3Cof2 = cofactor_matrix3(b, 0, 2);

	bool testDetMat3 = essentially_equal(testDet3, -196.0f) && essentially_equal(testDet3Cof0, 56.0f) &&
		essentially_equal(testDet3Cof1, 12.0f) && essentially_equal(testDet3Cof2, -46.0f);

	if (testDetMat3)
		std::cout << "Calculate Determinant of 3x3 Matrix: Test Passed" << std::endl;
	else
		std::cout << "Calculate Determinant of 3x3 Matrix: Test Failed" << std::endl;

	//Test 4x4 Determinant
	mat4.m[0][0] = -2.0f;	mat4.m[0][1] = -8.0f;	mat4.m[0][2] = 3.0f;	mat4.m[0][3] = 5.0f;
	mat4.m[1][0] = -3.0f;	mat4.m[1][1] = 1.0f;	mat4.m[1][2] = 7.0f;	mat4.m[1][3] = 3.0f;
	mat4.m[2][0] = 1.0f;	mat4.m[2][1] = 2.0f;	mat4.m[2][2] = -9.0f;	mat4.m[2][3] = 6.0f;
	mat4.m[3][0] = -6.0f;	mat4.m[3][1] = 7.0f;	mat4.m[3][2] = 7.0f;	mat4.m[3][3] = -9.0f;

	float testDet4 = det(mat4);

	if(essentially_equal(testDet4,-4071.0f))
		std::cout << "Calculate Determinant of 4x4 Matrix: Test Passed" << std::endl;
	else
		std::cout << "Calculate Determinant of 4x4 Matrix: Test Failed" << std::endl;

	std::cout << std::endl << std::endl;
}

void test_matrix_operations()
{
	std::cout << " Test Matrix Transpose" << std::endl;

	Matrix4 a,b;

	a.m[0][0] = 0.0f;	a.m[0][1] = 9.0f;	a.m[0][2] = 3.0f;	a.m[0][3] = 0.0f;
	a.m[1][0] = 9.0f;	a.m[1][1] = 8.0f;	a.m[1][2] = 0.0f;	a.m[1][3] = 8.0f;
	a.m[2][0] = 1.0f;	a.m[2][1] = 8.0f;	a.m[2][2] = 5.0f;	a.m[2][3] = 3.0f;
	a.m[3][0] = 0.0f;	a.m[3][1] = 0.0f;	a.m[3][2] = 5.0f;	a.m[3][3] = 8.0f;

	b = transpose(a);

	bool error = false;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (!essentially_equal(a.m[i][j], b.m[j][i]))
				error = true;
		}

	if (!error)
		std::cout << "Transpose Test Passed" << std::endl;
	else
		std::cout << "Transpose Test Failed" << std::endl;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << b.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void test_matrix_multiplication()
{
	std::cout << "Matrix Multuplicatio Tests:" << std::endl << std::endl;

	//Matrix-Matrix Multiplcation
	Matrix4 a, b, c;

	a.m[0][0] = 1.0f;	a.m[0][1] = 2.0f;	a.m[0][2] = 3.0f;	a.m[0][3] = 4.0f;
	a.m[1][0] = 5.0f;	a.m[1][1] = 6.0f;	a.m[1][2] = 7.0f;	a.m[1][3] = 8.0f;
	a.m[2][0] = 9.0f;	a.m[2][1] = 8.0f;	a.m[2][2] = 7.0f;	a.m[2][3] = 6.0f;
	a.m[3][0] = 5.0f;	a.m[3][1] = 4.0f;	a.m[3][2] = 3.0f;	a.m[3][3] = 2.0f;

	b.m[0][0] = -2.0f;	b.m[0][1] = 1.0f;	b.m[0][2] = 2.0f;	b.m[0][3] = 3.0f;
	b.m[1][0] = 3.0f;	b.m[1][1] = 2.0f;	b.m[1][2] = 1.0f;	b.m[1][3] = -1.0f;
	b.m[2][0] = 4.0f;	b.m[2][1] = 3.0f;	b.m[2][2] = 6.0f;	b.m[2][3] = 5.0f;
	b.m[3][0] = 1.0f;	b.m[3][1] = 2.0f;	b.m[3][2] = 7.0f;	b.m[3][3] = 8.0f;

	c = a*b;

	bool row1 = essentially_equal(c.m[0][0],20.0f) && essentially_equal(c.m[0][1], 22.0f) && essentially_equal(c.m[0][2], 50.0f)&& essentially_equal(c.m[0][3], 48.0f);
	bool row2 = essentially_equal(c.m[1][0], 44.0f) && essentially_equal(c.m[1][1], 54.0f) && essentially_equal(c.m[1][2], 114.0f) && essentially_equal(c.m[1][3], 108.0f);
	bool row3 = essentially_equal(c.m[2][0], 40.0f) && essentially_equal(c.m[2][1], 58.0f) && essentially_equal(c.m[2][2], 110.0f) && essentially_equal(c.m[2][3], 102.0f);
	bool row4 = essentially_equal(c.m[3][0], 16.0f) && essentially_equal(c.m[3][1], 26.0f) && essentially_equal(c.m[3][2], 46.0f) && essentially_equal(c.m[3][3], 42.0f);

	if (row1 && row2 && row3 && row4)
		std::cout << " C = A*B Matrix Multiplication: Test Passed" << std::endl;
	else
		std::cout << " C = A*B Matrix Multiplication: Test Failed" << std::endl;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << c.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	//Matrix-Tuple Multiplication
	a.m[0][0] = 1.0f;	a.m[0][1] = 2.0f;	a.m[0][2] = 3.0f;	a.m[0][3] = 4.0f;
	a.m[1][0] = 2.0f;	a.m[1][1] = 4.0f;	a.m[1][2] = 4.0f;	a.m[1][3] = 2.0f;
	a.m[2][0] = 8.0f;	a.m[2][1] = 6.0f;	a.m[2][2] = 4.0f;	a.m[2][3] = 1.0f;
	a.m[3][0] = 0.0f;	a.m[3][1] = 0.0f;	a.m[3][2] = 0.0f;	a.m[3][3] = 1.0f;

	Tuple t(1.0f,2.0f,3.0f,1.0f);
	Tuple ans = a*t;

	if (essentially_equal(ans.x, 18.0f) && essentially_equal(ans.y, 24.0f) && essentially_equal(ans.z, 33.0) && essentially_equal(ans.w, 1.0))
		std::cout << " Tuple t = Matrix A * Tuple b: Test Passed" << std::endl;
	else
		std::cout << " Tuple t = Matrix A * Tuple b: Test Failed" << std::endl;

	std::cout << ans.x << "		" << ans.y << "		" << ans.z << "		" << ans.w << std::endl;

	//Identity Matrix Test
	a.m[0][0] = 0.0f;	a.m[0][1] = 1.0f;	a.m[0][2] = 2.0f;	a.m[0][3] = 4.0f;
	a.m[1][0] = 1.0f;	a.m[1][1] = 2.0f;	a.m[1][2] = 4.0f;	a.m[1][3] = 8.0f;
	a.m[2][0] = 2.0f;	a.m[2][1] = 4.0f;	a.m[2][2] = 8.0f;	a.m[2][3] = 16.0f;
	a.m[3][0] = 4.0f;	a.m[3][1] = 8.0f;	a.m[3][2] = 16.0f;	a.m[3][3] = 32.0f;

	std::cout << "Test for Identity Matrix mult by Matrix:" << std::endl;
	Matrix4 I;
	Matrix4 res = a*I;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << res.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	std::cout << "Test for Identity Matrix mult by Tuple" << std::endl;

	Tuple res1 = I*Tuple(1.0f, 2.0f, 3.0f, 4.0f);
	std::cout << res1.x << "		" << res1.y << "		" << res1.z << "		" << res1.w << std::endl;

	std::cout << std::endl << std::endl;
}

void test_matrix_equality()
{
	std::cout << "Test Matrix Equality:" << std::endl << std::endl;

	Matrix4 a, b;

	a.m[0][0] = 1.0f;	a.m[0][1] = 2.0f;	a.m[0][2] = 3.0f;	a.m[0][3] = 4.0f;
	a.m[1][0] = 5.0f;	a.m[1][1] = 6.0f;	a.m[1][2] = 7.0f;	a.m[1][3] = 8.0f;
	a.m[2][0] = 9.0f;	a.m[2][1] = 8.0f;	a.m[2][2] = 7.0f;	a.m[2][3] = 6.0f;
	a.m[3][0] = 5.0f;	a.m[3][1] = 4.0f;	a.m[3][2] = 3.0f;	a.m[3][3] = 2.0f;

	b = a;

	if (a == b)
		std::cout << "A = B: Test Passed" << std::endl;
	else 
		std::cout << "A = B: Test Failed" << std::endl;

	b.m[0][0] = 2.0f;	b.m[0][1] = 3.0f;	b.m[0][2] = 4.0f;	b.m[0][3] = 5.0f;
	b.m[1][0] = 6.0f;	b.m[1][1] = 7.0f;	b.m[1][2] = 8.0f;	b.m[1][3] = 9.0f;
	b.m[2][0] = 8.0f;	b.m[2][1] = 7.0f;	b.m[2][2] = 6.0f;	b.m[2][3] = 5.0f;
	b.m[3][0] = 4.0f;	b.m[3][1] = 3.0f;	b.m[3][2] = 2.0f;	b.m[3][3] = 1.0f;

	if (!(a == b))
		std::cout << "A != B: Test Passed" << std::endl;
	else
		std::cout << "A != B: Test Failed" << std::endl;
}

void test_matrix_assignment()
{
	std::cout << "Test 4x4 Matrix Assignment:" << std::endl;

	Matrix4 mat4;

	mat4.m[0][0] = 1.0f;	mat4.m[0][1] = 2.0f;	mat4.m[0][2] = 3.0f;	mat4.m[0][3] = 4.0f;
	mat4.m[1][0] = 5.5f;	mat4.m[1][1] = 6.5f;	mat4.m[1][2] = 7.5f;	mat4.m[1][3] = 8.5f;
	mat4.m[2][0] = 9.0f;	mat4.m[2][1] = 10.0f;	mat4.m[2][2] = 11.0f;	mat4.m[2][3] = 12.0f;
	mat4.m[3][0] = 13.5f;	mat4.m[3][1] = 14.5f;	mat4.m[3][2] = 15.5f;	mat4.m[3][3] = 16.5f;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << mat4.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}

	std::cout << "Test 3x3 Matrix Assignment:" << std::endl;

	Matrix3 mat3;

	mat3.m[0][0] = -3.0f;	mat3.m[0][1] = 5.0f;	mat3.m[0][2] = 0.0f;	
	mat3.m[1][0] = 1.0f;	mat3.m[1][1] = -2.0f;	mat3.m[1][2] = -7.0f;	
	mat3.m[2][0] = 0.0f;	mat3.m[2][1] = 1.0f;	mat3.m[2][2] = 1.0f;	

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			std::cout << mat3.m[y][x] << "           ";
		}
		std::cout << std::endl;
	}
	

	std::cout << std::endl;
};

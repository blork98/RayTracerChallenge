#ifndef MATRIX_H_
#define MATRIX_H_

#include "Tuple.h"

namespace RTC
{
	class Matrix4
	{

	public:

		double	m[4][4];								

		Matrix4();									
		Matrix4(const Matrix4& mat);						

		Matrix4&	operator= (const Matrix4& rhs);
		
	};

	class Matrix3
	{

	public:

		double	m[3][3];

		Matrix3();
		Matrix3(const Matrix3& mat);

		Matrix3&	operator= (const Matrix3& rhs);
		
	};

	class Matrix2
	{

	public:

		double	m[2][2];

		Matrix2();
		Matrix2(const Matrix2& mat);

		Matrix2&	operator= (const Matrix2& rhs);
		
	};

	//matrix equality operator
	bool operator==(const Matrix4& rhs, const Matrix4& lhs);
	bool operator==(const Matrix3& rhs, const Matrix3& lhs);
	bool operator==(const Matrix2& rhs, const Matrix2& lhs);

	bool operator!=(const Matrix4& rhs, const Matrix4& lhs);
	bool operator!=(const Matrix3& rhs, const Matrix3& lhs);
	bool operator!=(const Matrix2& rhs, const Matrix2& lhs);

	Matrix4 operator*(const Matrix4& rhs, const Matrix4& lhs);
	Tuple operator*(const Matrix4& rhs, const Tuple& t);

	Matrix4 transpose(const Matrix4& mat);

	double det(const Matrix2& m);
	double det(const Matrix3& m);
	double det(const Matrix4& m);

	bool is_invertible(const Matrix4& m);
	bool get_inverse(const Matrix4& mat, Matrix4& inv);

	Matrix2 get_submatrix2(const Matrix3& mat, unsigned int row, unsigned int col);
	Matrix3 get_submatrix3(const Matrix4& mat, unsigned int row, unsigned int col);

	double minor_matrix3(const Matrix3& mat, unsigned int row, unsigned int col);
	double cofactor_matrix3(const Matrix3& mat, unsigned int row, unsigned int col);

	double minor_matrix4(const Matrix4& mat, unsigned int row, unsigned int col);
	double cofactor_matrix4(const Matrix4& mat, unsigned int row, unsigned int col);
}

#endif
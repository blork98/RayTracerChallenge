#include "MATRIX.h"

#include "Constants.h"

namespace RTC
{
	//Default matrix is Identity
	Matrix4::Matrix4()
	{
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++) {
				if (x == y)
					m[x][y] = 1.0;
				else
					m[x][y] = 0.0;
			}
	}

	Matrix4::Matrix4(const Matrix4& mat)
	{
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				m[x][y] = mat.m[x][y];
	}

	Matrix4& Matrix4::operator= (const Matrix4& rhs) 
	{
		if (this == &rhs)
			return (*this);

		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				m[x][y] = rhs.m[x][y];

		return (*this);
	}

	Matrix3::Matrix3()
	{
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) {
				if (x == y)
					m[x][y] = 1.0;
				else
					m[x][y] = 0.0;
			}
	}

	Matrix3::Matrix3(const Matrix3& mat)
	{
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				m[x][y] = mat.m[x][y];
	}

	Matrix3& Matrix3::operator= (const Matrix3& rhs)
	{
		if (this == &rhs)
			return (*this);

		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				m[x][y] = rhs.m[x][y];

		return (*this);
	}

	Matrix2::Matrix2()
	{
		for (int x = 0; x < 2; x++)
			for (int y = 0; y < 2; y++) {
				if (x == y)
					m[x][y] = 1.0;
				else
					m[x][y] = 0.0;
			}
	}

	Matrix2::Matrix2(const Matrix2& mat)
	{
		for (int x = 0; x < 2; x++)
			for (int y = 0; y < 2; y++)
				m[x][y] = mat.m[x][y];
	}

	Matrix2& Matrix2::operator= (const Matrix2& rhs)
	{
		if (this == &rhs)
			return (*this);

		for (int x = 0; x < 2; x++)
			for (int y = 0; y < 2; y++)
				m[x][y] = rhs.m[x][y];

		return (*this);
	}

	bool operator==(const Matrix4& rhs, const Matrix4& lhs)
	{
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				if (!essentially_equal(rhs.m[row][col], lhs.m[row][col]))
					return false;

		return true;
	}

	bool operator==(const Matrix3& rhs, const Matrix3& lhs)
	{
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				if (!essentially_equal(rhs.m[row][col], lhs.m[row][col]))
					return false;

		return true;
	}

	bool operator==(const Matrix2& rhs, const Matrix2& lhs)
	{
		for (int row = 0; row < 2; row++)
			for (int col = 0; col < 2; col++)
				if (!essentially_equal(rhs.m[row][col], lhs.m[row][col]))
					return false;

		return true;
	}

	bool operator!=(const Matrix4& rhs, const Matrix4& lhs)
	{
		return !(rhs == lhs);
	}

	bool operator!=(const Matrix3& rhs, const Matrix3& lhs)
	{
		return !(rhs == lhs);
	}

	bool operator!=(const Matrix2& rhs, const Matrix2& lhs)
	{
		return !(rhs == lhs);
	}

	Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 product;

		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++) 
			{
				double sum = 0.0;

				for (int j = 0; j < 4; j++)
					sum += a.m[x][j] * b.m[j][y];

				product.m[x][y] = sum;
			}

		return product;
	}

	Tuple operator*(const Matrix4& rhs, const Tuple& t)
	{
		Tuple product;

		product.x = 0.0f;
		product.y = 0.0f;
		product.z = 0.0f;
		product.w = 0.0f;

		double v[4];
		v[0] = t.x;
		v[1] = t.y;
		v[2] = t.z;
		v[3] = t.w;

		for (int col = 0; col < 4; ++col)
		{
			product.x += rhs.m[0][col] * v[col];
			product.y += rhs.m[1][col] * v[col];
			product.z += rhs.m[2][col] * v[col];
			product.w += rhs.m[3][col] * v[col];
		}

		return product;
	}

	Matrix4 transpose(const Matrix4& mat)
	{
		Matrix4 res;

		for (int row = 0; row < 4; ++row)
			for (int col = row; col < 4; ++col)
			{
				res.m[row][col] = mat.m[col][row];
				res.m[col][row] = mat.m[row][col];
			}

		return res;
	}

	double det(const Matrix2& m)
	{
		double res = 0.0f;

		res = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];

		return res;
	}

	Matrix2 get_submatrix2(const Matrix3& mat, unsigned int row, unsigned int col)
	{
		Matrix2 subMatrix;

		unsigned int rowCtr = 0, colCtr = 0;

		for (unsigned int r = 0; r < 3; ++r)
			for (unsigned int c = 0; c < 3; ++c)
			{
				if (!((r == row) || (c == col)))
				{
					subMatrix.m[rowCtr][colCtr] = mat.m[r][c];
					++colCtr;

					if (colCtr == 2)
					{
						++rowCtr;
						colCtr = 0;
					}
				}
			}

		return subMatrix;
	}

	Matrix3 get_submatrix3(const Matrix4& mat, unsigned int row, unsigned int col)
	{
		Matrix3 subMatrix;

		unsigned int rowCtr = 0, colCtr = 0;

		for (unsigned int r = 0; r < 4; ++r)
			for (unsigned int c = 0; c < 4; ++c)
			{
				if (!((r == row) || (c == col)))
				{
					subMatrix.m[rowCtr][colCtr] = mat.m[r][c];
					++colCtr;

					if (colCtr == 3)
					{
						++rowCtr;
						colCtr = 0;
					}
				}
			}

		return subMatrix;
	}

	double minor_matrix3(const Matrix3& mat, unsigned int row, unsigned int col)
	{
		double result = 0.0f;

		Matrix2 b = get_submatrix2(mat, row, col);
		result = det(b);

		return result;
	}

	double minor_matrix4(const Matrix4& mat, unsigned int row, unsigned int col)
	{
		double result = 0.0f;

		Matrix3 b = get_submatrix3(mat, row, col);
		result = det(b);

		return result;
	}

	double cofactor_matrix3(const Matrix3& mat, unsigned int row, unsigned int col)
	{
		double result = minor_matrix3(mat, row, col);

		int isEven = (row + col)%2;

		if (isEven != 0)
			result *= -1.0f;

		return result;
	}

	double cofactor_matrix4(const Matrix4& mat, unsigned int row, unsigned int col)
	{
		double result = minor_matrix4(mat, row, col);

		int isEven = (row + col) % 2;

		if (isEven != 0)
			result *= -1.0f;

		return result;
	}

	double det(const Matrix3& m)
	{
		double result = 0.0f;

		for (unsigned int i = 0; i < 3; ++i)
		{
			result += m.m[0][i] * cofactor_matrix3(m,0,i);
		}

		return result;
	}

	double det(const Matrix4& m)
	{
		double result = 0.0f;

		for (unsigned int i = 0; i < 4; ++i)
		{
			result += m.m[0][i] * cofactor_matrix4(m, 0, i);
		}

		return result;
	}

	bool is_invertible(const Matrix4& m) 
	{
		bool result = false;

		double det4 = det(m);

		if (essentially_equal(0.0f, det4))
			result = false;
		else
			result = true;

		return result;
	}

	bool get_inverse(const Matrix4& mat, Matrix4& inv)
	{
		if (!is_invertible(mat))
			return false;

		double determinant = det(mat);
		double c = 0.0f;

		for (unsigned int row = 0; row < 4; ++row)
			for (unsigned int col = 0; col < 4; ++col)
			{
				c = cofactor_matrix4(mat, row, col);
				inv.m[col][row] = c / determinant;
			}


		return true;
	}

}
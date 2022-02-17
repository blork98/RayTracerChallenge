#include "Transform.h"

#include <cmath>

namespace RTC
{

	Transform::Transform()
	{
		for (unsigned int i = 0; i < 4; ++i)
			for (unsigned int j = 0; j < 4; ++j)
			{
				trans.m[i][j] = 0.0f;
				inv_trans.m[i][j] = 0.0f;
				if (i == j)
				{
					trans.m[i][j] = 1.0f;
					inv_trans.m[i][j] = 1.0f;
				}
			}
	}

	Transform::Transform(const Matrix4& transMat)
	{
		trans = transMat;
		get_inverse(trans, inv_trans);
	}

	Transform::Transform(const Transform& transform)
	{
		for (unsigned int i = 0; i < 4; ++i)
			for (unsigned int j = 0; j < 4; ++j)
			{
				trans.m[i][j] = transform.trans.m[i][j];
				inv_trans.m[i][j] = transform.inv_trans.m[i][j];
			}
	}

	void Transform::set_to_identity()
	{
		for (unsigned int i = 0; i < 4; ++i)
			for (unsigned int j = 0; j < 4; ++j)
			{
				trans.m[i][j] = 0.0f;
				inv_trans.m[i][j] = 0.0f;
				if (i == j)
				{
					trans.m[i][j] = 1.0f;
					inv_trans.m[i][j] = 1.0f;
				}
			}
	}

	Transform::~Transform()
	{}

	Transform& Transform::operator=(const Transform& rhs)
	{
		if (this == &rhs)
			return (*this);

		for (unsigned int i = 0; i < 4; ++i)
			for (unsigned int j = 0; j < 4; ++j)
			{
				trans.m[i][j] = rhs.trans.m[i][j];
				inv_trans.m[i][j] = rhs.inv_trans.m[i][j];
			}

		return (*this);
	}

	Matrix4 Transform::get_transform() const
	{
		return trans;
	}

	Matrix4 Transform::get_inverse_transform() const
	{
		return inv_trans;
	}

	Tuple Transform::apply_transform(const Tuple& tuple) const
	{
		Tuple result;

		result = trans*tuple;

		return result;
	}

	Tuple Transform::apply_inverse_transform(const Tuple& tuple) const
	{
		Tuple result;

		result = inv_trans*tuple;

		return result;
	}

	Tuple Transform::apply_transform_trans(const Tuple& tuple) const
	{
		Tuple result;

		Matrix4 transT = transpose(this->trans);
		result = transT*tuple;

		return result;
	}
	
	Tuple Transform::apply_inverse_transform_trans(const Tuple& tuple) const
	{
		Tuple result;

		Matrix4 invTransT = transpose(this->inv_trans);
		result = invTransT*tuple;

		return result;
	}

	Translation::Translation()
		:Transform()
	{};

	Translation::Translation(double x, double y, double z)
		:Transform()
	{
		trans.m[0][3] = x;
		trans.m[1][3] = y;
		trans.m[2][3] = z;

		get_inverse(trans, inv_trans);
	}

	Translation::Translation(const Translation& trans)
		:Transform(trans)
	{}

	Translation& Translation::operator=(const Translation& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		return (*this);
	}

	Translation::~Translation()
	{};

	Scaling::Scaling()
		: Transform()
	{}

	Scaling::Scaling(double x, double y, double z)
		:Transform()
	{
		trans.m[0][0] = x;
		trans.m[1][1] = y;
		trans.m[2][2] = z;

		get_inverse(trans, inv_trans);
	}

	Scaling::Scaling(const Scaling& trans)
		:Transform(trans)
	{}

	Scaling::~Scaling()
	{}

	Scaling& Scaling::operator=(const Scaling& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		return (*this);
	}

	Rotation::Rotation()
		:Transform()
	{}

	Rotation::Rotation(const Rotation& trans)
		:Transform(trans)
	{}

	Rotation& Rotation::operator=(const Rotation& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		return (*this);
	}
	
	Rotation::~Rotation()
	{}

	void Rotation::rotate_x(double r)
	{
		trans.m[1][1] = std::cos(r);
		trans.m[1][2] = -1.0f*std::sin(r);
		trans.m[2][1] = std::sin(r);
		trans.m[2][2] = std::cos(r);

		get_inverse(trans, inv_trans);
	}

	void Rotation::rotate_y(double r)
	{
		trans.m[0][0] = std::cos(r);
		trans.m[0][2] = std::sin(r);
		trans.m[2][0] = -1.0f*std::sin(r);
		trans.m[2][2] = std::cos(r);

		get_inverse(trans, inv_trans);
	}

	void Rotation::rotate_z(double r)
	{
		trans.m[0][0] = std::cos(r);
		trans.m[0][1] = -1.0f*std::sin(r);
		trans.m[1][0] = std::sin(r);
		trans.m[1][1] = std::cos(r);

		get_inverse(trans, inv_trans);
	}

	Shearing::Shearing()
		:Transform()
	{}

	Shearing::Shearing(double xy, double xz, double yx, double yz, double zx, double zy)
		:Transform()
	{
		trans.m[0][1] = xy;
		trans.m[0][2] = xz;
		trans.m[1][0] = yx;
		trans.m[1][2] = yz;
		trans.m[2][0] = zx;
		trans.m[2][1] = zy;

		get_inverse(trans, inv_trans);
	}

	Shearing::Shearing(const Shearing& trans)
		:Transform(trans)
	{}

	Shearing& Shearing::operator=(const Shearing& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		return (*this);
	}

	Shearing::~Shearing()
	{}

	CompoundTransform::CompoundTransform()
		:Transform()
	{}

	CompoundTransform::CompoundTransform(std::vector<std::shared_ptr<Transform>>& transforms_)
		: Transform(), transforms(transforms_)
	{
		
		for (auto transform : transforms)
		{
			this->trans = this->trans * transform->get_transform();
			this->inv_trans = this->inv_trans * transform->get_inverse_transform();
		}
	}

	CompoundTransform::CompoundTransform(const CompoundTransform& trans)
		: Transform(), transforms(trans.transforms)
	{}

	CompoundTransform& CompoundTransform::operator=(const CompoundTransform& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		transforms = rhs.transforms;

		return (*this);
	}

	CompoundTransform::~CompoundTransform()
	{}

	Tuple CompoundTransform::apply_transform(Tuple& tuple) const
	{
		Tuple result = tuple;

		for (auto x : transforms)
			result = x->apply_transform(result);

		return result;
	}

	Tuple CompoundTransform::apply_inverse_transform(Tuple& tuple) const
	{
		Tuple result = tuple;

		for (auto x : transforms)
			result = x->apply_inverse_transform(result);

		return result;
	}

	ViewTransform::ViewTransform()
		:Transform()
	{}

	ViewTransform::ViewTransform(const Shearing& trans)
		:Transform(trans)
	{}

	ViewTransform::ViewTransform(Tuple from, Tuple to, Tuple up)
	{
		//Create inverse transform
		Tuple forward = normalize_vector(to - from);
		Tuple upn = normalize_vector(up);	
		Tuple left = vector_cross_product(forward, upn);
		Tuple true_up = vector_cross_product(left, forward);

		//Orientation Matrix
		trans.m[0][0] = left.x;
		trans.m[0][1] = left.y;
		trans.m[0][2] = left.z;

		trans.m[1][0] = true_up.x;
		trans.m[1][1] = true_up.y;
		trans.m[1][2] = true_up.z;

		trans.m[2][0] = -1.0*forward.x;
		trans.m[2][1] = -1.0*forward.y;
		trans.m[2][2] = -1.0*forward.z;

		trans = trans * (Translation(-1.0*from.x, -1.0*from.y, -1.0*from.z)).get_transform();
	
		//Create inverse transform
		get_inverse(trans, inv_trans);
	}

	ViewTransform& ViewTransform::operator=(const ViewTransform& rhs)
	{
		if (this == &rhs)
			return (*this);

		Transform::operator=(rhs);

		return (*this);
	}

	ViewTransform::~ViewTransform()
	{}

}
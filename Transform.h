#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Tuple.h"
#include "MATRIX.h"

#include <memory>
#include <vector>

namespace RTC
{
	class Transform
	{
	public:
		Transform();
		Transform(const Matrix4& transMat);
		Transform(const Transform& transform);
		virtual ~Transform();

		Transform& operator=(const Transform& rhs);

		virtual Tuple apply_transform(const Tuple& tuple) const;
		virtual Tuple apply_inverse_transform(const Tuple& tuple) const;
		virtual Tuple apply_transform_trans(const Tuple& tuple) const;
		virtual Tuple apply_inverse_transform_trans(const Tuple& tuple) const;

		void set_to_identity();
		Matrix4 get_transform() const;
		Matrix4 get_inverse_transform() const;

	protected:
		Matrix4 trans;
		Matrix4 inv_trans;
	};

	class CompoundTransform : public Transform
	{
	public:
		CompoundTransform();
		CompoundTransform(std::vector<std::shared_ptr<Transform>>& transforms_);
		CompoundTransform(const CompoundTransform& trans);
		CompoundTransform& operator=(const CompoundTransform& rhs);
		virtual ~CompoundTransform();

		virtual Tuple apply_transform(Tuple& tuple) const;
		virtual Tuple apply_inverse_transform(Tuple& tuple) const;

	private:
		std::vector<std::shared_ptr<Transform>> transforms;
	};

	class Translation : public Transform
	{
	public:
		Translation();
		Translation(double x, double y, double z);
		Translation(const Translation& trans);
		Translation& operator=(const Translation& rhs);
		virtual ~Translation();

	};

	class Scaling : public Transform
	{
	public:
		Scaling();
		Scaling(double x, double y, double z);
		Scaling(const Scaling& trans);
		Scaling& operator=(const Scaling& rhs);
		virtual ~Scaling();
	};

	class Rotation : public Transform
	{
	public:
		Rotation();
		Rotation(const Rotation& trans);
		Rotation& operator=(const Rotation& rhs);
		virtual ~Rotation();

		void rotate_x(double r);
		void rotate_y(double r);
		void rotate_z(double r);
	};

	class Shearing : public Transform
	{
	public:
		Shearing();
		Shearing(double xy, double xz, double yx, double yz, double zx, double zy);
		Shearing(const Shearing& trans);
		Shearing& operator=(const Shearing& rhs);
		virtual ~Shearing();
	};

	class ViewTransform : public Transform
	{
	public:
		ViewTransform();
		ViewTransform(Tuple from, Tuple to, Tuple up);
		ViewTransform(const Shearing& trans);
		ViewTransform& operator=(const ViewTransform& rhs);
		virtual ~ViewTransform();
	};

}

#endif
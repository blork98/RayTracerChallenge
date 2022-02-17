#include "Camera.h"
#include "Ray.h"
#include "World.h"
#include "Canvas.h"

#include <cmath>

namespace RTC
{

	Camera::Camera()
		:hsize(0),vsize(0),pixel_size(0),transform(nullptr),
		field_of_view(0.0),half_height(0.0),half_width(0.0)
	{
		transform = std::make_shared<Transform>();
	}

	Camera::Camera(int hsize_, int vsize_, double field_of_view_)
		:hsize(hsize_), vsize(vsize_),field_of_view(field_of_view_),
		transform(nullptr), pixel_size(0.0), half_height(0.0),half_width(0.0)
	{
		transform = std::make_shared<Transform>();
		calculate_piexel_size();
	}

	Camera::Camera(const Camera& rhs)
		: hsize(rhs.hsize), vsize(rhs.vsize), field_of_view(rhs.field_of_view),
		transform(rhs.transform), pixel_size(rhs.pixel_size),
		half_height(rhs.half_height), half_width(rhs.half_width)
	{}

	Camera::~Camera()
	{}

	double Camera::get_pixel_size() const
	{
		return pixel_size;
	}

	Camera& Camera::operator=(const Camera& rhs)
	{
		if (this == &rhs)
			return (*this);

		pixel_size = rhs.pixel_size;
		vsize = rhs.vsize;
		hsize = rhs.hsize;
		transform = rhs.transform;
		field_of_view = rhs.field_of_view;
		half_width = rhs.half_width;
		half_height = rhs.half_height;

		return (*this);
	}

	void Camera::set_transform(std::shared_ptr<Transform> transform)
	{
		this->transform = transform;
	}

	void Camera::calculate_piexel_size()
	{
		double half_view = std::tan(field_of_view*0.5);
		double aspect = (double) hsize / (double)vsize;

		if (aspect >= 1.0)
		{
			half_width = half_view;
			half_height = half_view / aspect;
		}
		else 
		{
			half_width = half_view*aspect;
			half_height = half_view;
		}

		pixel_size = 2.0*half_width / hsize;

	}

	Ray Camera::ray_for_pixel(int px, int py)
	{
		double xoffset = (px + 0.5)*pixel_size;
		double yoffset = (py + 0.5)*pixel_size;

		double world_x = half_width - xoffset;
		double world_y = half_height - yoffset;

		Tuple pixel = transform->apply_inverse_transform(create_tuple_point(world_x, world_y, -1.0f));
		Tuple origin = transform->apply_inverse_transform(create_tuple_point(0.0f, 0.0f, 0.0f));
		Tuple direction = normalize_vector(pixel-origin);

		return Ray(origin, direction);
	}

	int Camera::get_hsize() const
	{
		return hsize;
	}

	int Camera::get_vsize() const
	{
		return vsize;
	}

	void Camera::render(World& world, Canvas& image)
	{
		//image = Canvas(hsize, vsize); Test for image size here
		
		for (int y = 0; y < vsize; ++y)
		{
			for (int x = 0; x < hsize; ++x)
			{
				Ray ray = ray_for_pixel(x,y);
				image(x, y) = world.color_at(ray,world.num_reflect_recurions);
			}
		}
	}

}
#ifndef CAMERA_H
#define CAMERA_H_

#include "Transform.h"

#include <memory>

namespace RTC
{
	class Ray;
	struct World;
	struct Canvas;

	class Camera
	{
	public:
		Camera();
		Camera(int hsize, int vsize, double field_of_view);
		Camera(const Camera& rhs);
		virtual ~Camera();

		Camera& operator=(const Camera& rhs);

		void set_transform(std::shared_ptr<Transform> transform);
		double get_pixel_size() const;
		int get_hsize() const;
		int get_vsize() const;
	
		Ray ray_for_pixel(int px, int py);
		void render(World& world, Canvas& image);

	private:
		int hsize, vsize;
		double field_of_view;
		double pixel_size;
		double half_width, half_height;

		void calculate_piexel_size();

		std::shared_ptr<Transform> transform;
	};

}
#endif
#ifndef LIGHT_H_
#define LIGHT_H_

#include "Canvas.h"
#include "Tuple.h"

namespace RTC
{
	struct ShadeInfo;

	class Light
	{
	public:
		Light();
		~Light();

		virtual Color get_intensity(const ShadeInfo& s) const = 0;
		virtual Tuple get_position() const = 0;
		virtual Tuple get_direction(const ShadeInfo& s) const = 0;

	};

	class PointLight : public Light
	{
	public:
		PointLight();
		PointLight(const Tuple& position, const Color& intensity);
		~PointLight();

		virtual Color get_intensity(const ShadeInfo& s) const;
		virtual Tuple get_position() const;
		virtual Tuple get_direction(const ShadeInfo& s) const;

		void set_position(Tuple pos);
		void set_intensity(Color col);

	private:
		Color intensity;
		Tuple position;
	};

	struct PhongMaterial
	{
		PhongMaterial();
		double ambient, diffuse, specular, shininess;
	};

}

#endif
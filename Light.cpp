#include "Light.h"
#include "Canvas.h"
#include "GeometricObject.h"

namespace RTC
{
	Light::Light()
	{}

	Light::~Light()
	{}

	PointLight::PointLight()
		:Light()
	{}

	PointLight::PointLight(const Tuple& pos, const Color& ints)
		:Light(), position(pos), intensity(ints)
	{}

	PointLight::~PointLight()
	{}

	Color PointLight::get_intensity(const ShadeInfo& s) const
	{
		return intensity;
	}

	Tuple PointLight::get_position() const
	{
		return position;
	}

	Tuple PointLight::get_direction(const ShadeInfo& s) const
	{
		return normalize_vector(position - s.hit_point);
	}

	void PointLight::set_position(Tuple pos)
	{
		position = pos;
	}

	void PointLight::set_intensity(Color col)
	{
		intensity = col;
	}

	PhongMaterial::PhongMaterial()
	{
		ambient = 0.1f;
		diffuse = 0.9f;
		specular = 0.9f; 
		shininess = 200.0f;
	}

}
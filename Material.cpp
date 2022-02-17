#include "Material.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Utility.h"
#include "World.h"
#include "Constants.h"

#include <cmath>
#include <iostream>
#include <iomanip>

namespace RTC
{
	Material::Material()
		:pattern(nullptr), reflective(0.0),
		transparency(0.0), refractive_index(1.0)
	{}

	Material::Material(const Material& mat)
		:pattern(mat.pattern),reflective(mat.reflective),
		transparency(mat.transparency),refractive_index(mat.refractive_index)
	{}

	Material::~Material()
	{}

	double Material::get_refractive_index() const
	{
		return refractive_index;
	}

	Material& Material::operator=(const Material& rhs)
	{
		if (this == &rhs)
			return (*this);

		pattern = rhs.pattern;
		reflective = rhs.reflective;
		transparency = rhs.transparency;
		refractive_index = rhs.refractive_index;

		return (*this);
	}

	void Material::set_refractive_index(double ref_i)
	{
		refractive_index = ref_i;
	}

	void  Material::set_transparency(double trans)
	{
		transparency = trans;
	}

	void  Material::set_reflective(double ref)
	{
		reflective = ref;
	}

	void Material::set_pattern(std::shared_ptr<Pattern> pattern_)
	{
		pattern = pattern_;
	}

	std::shared_ptr<Pattern> Material::get_pattern()
	{
		return pattern;
	}

	Color Material::lighting(std::shared_ptr<Light> light, ShadeInfo& s)
	{
		return Color(0.0f, 0.0f, 0.0f);
	}

	Phong::Phong()
		:Material(), color(1.0f,1.0f,1.0f)
	{
		ambient = 0.1f;
		diffuse = 0.9f;
		specular = 0.9f;
		shininess = 200.0f;
	}

	Phong::Phong(const Phong& mat)
		:Material(mat), color(mat.color), ambient(mat.ambient),
		diffuse(mat.diffuse), specular(mat.specular), shininess(mat.shininess)
	{}

	Phong::~Phong()
	{}

	Phong& Phong::operator=(const Phong& rhs)
	{
		if (this == &rhs)
			return (*this);

		Material::operator=(rhs);

		color = rhs.color;
		ambient = rhs.ambient;
		shininess = rhs.shininess;
		diffuse = rhs.diffuse;
		specular = rhs.specular;

		return (*this);
	}

	void Phong::set_ambient(double val)
	{
		this->ambient = val;
	}

	void Phong::set_diffuse(double val)
	{
		this->diffuse = val;
	}

	void Phong::set_specular(double val)
	{
		this->specular = val;
	}

	void Phong::set_shininess(double val)
	{
		this->shininess = val;
	}

	void Phong::set_color(Color col)
	{
		this->color = col;
	}

	Color Phong::lighting(std::shared_ptr<Light> light, ShadeInfo& s)
	{
		//check if in shadow
		Tuple hit_point_l = s.over_point;
		//if (s.in_shadow)
		//	hit_point_l = s.over_point;
		//else
		//	hit_point_l = s.hit_point;

		//Check for pattern
		Color color_p;
		if (pattern != nullptr)
			color_p = pattern->pattern_at_object(hit_point_l,s);
		else
			color_p = this->color;

		// combine the surface color with the light's color/intensity
		Color effective_color = color_p*light->get_intensity(s);

		// find the direction to the light source
		//Tuple lightv = normalize_vector(  light->get_direction(s));
		Tuple lightv = normalize_vector(light->get_position() - hit_point_l);

		// compute the ambient contribution
		Color ambient_comp = effective_color*this->ambient;

		Color diffuse_comp;
		Color specular_comp;

		Tuple reflectv;
		double reflect_dot_eye;

		// light_dot_normal represents the cosine of the angle between the
		// light vector and the normal vector.A negative number means the
		// light is on the other side of the surface.
		double light_dot_normal = vector_dot_product(lightv, s.normalv);

		if (light_dot_normal < 0.0)
		{
			diffuse_comp = Color(0.0f, 0.0f, 0.0f);
			specular_comp = Color(0.0f, 0.0f, 0.0f);
		}
		else
		{
			// compute the diffuse contribution
			diffuse_comp = effective_color*this->diffuse*light_dot_normal;

			// reflect_dot_eye represents the cosine of the angle between the
			// reflection vector and the eye vector.A negative number means the
			// light reflects away from the eye.
			reflectv = reflect(-1.0f*lightv, s.normalv);
			reflect_dot_eye = vector_dot_product(reflectv, s.eyev);

			if( reflect_dot_eye <= 0.0f)
				specular_comp = Color(0.0f, 0.0f, 0.0f);
			else
			{
				// compute the specular contribution
				double factor = std::pow(reflect_dot_eye,this->shininess);
				specular_comp = light->get_intensity(s)*this->specular*factor;
			}
		}

		// Add the three contributions together to get the final shading
		if (!s.in_shadow)
			return specular_comp + ambient_comp + diffuse_comp;
		else
			return ambient_comp;
	}

	Color Material::shade_hit(World& w, ShadeInfo& s, int remaining)
	{
		Color surace = Color(0.0f, 0.0f, 0.0f);
		bool shadowed;

		unsigned int num_lights = w.lights.size();

		for (unsigned int i = 0; i < num_lights; ++i)
		{
			s.in_shadow = w.is_shadowed(s.over_point,w.lights[i]);
			//if shadowed set s.hit_point to s.over_point
			//s.hit_point = s.over_point;

			surace = surace + lighting(w.lights[i], s);
		}

		Color reflected = reflected_color(w, s,remaining);
		Color refracted = refracted_color(w, s, remaining);

		if (reflective > 0.0 && transparency > 0.0)
		{
			double reflectance = schlick(s);
			return surace + reflected*reflectance + refracted*(1 - reflectance);
		}
		else {
			return surace + reflected + refracted;

		}

	}

	Color Material::reflected_color(World& w, ShadeInfo& s, int remaining)
	{
		return Black;
	}

	Color Phong::reflected_color(World& w, ShadeInfo& s, int remaining)
	{
		if (remaining <= 0.0)
			return Color(0.0, 0.0, 0.0);

		if (reflective <= 0.0)
			return Color(0.0, 0.0, 0.0);

		Ray reflect(s.over_point,s.reflectv);
		Color res = w.color_at(reflect,remaining-1);
		return reflective*res;
	}

	Color Material::refracted_color(World& w, ShadeInfo& s, int remaining)
	{
		if (floatCompareSpecified(this->transparency, 0.0, 0.0000001))
			return Black;

		if (remaining == 0)
			return Black;

		//Check for Total Internal REflection
		double n_ratio = s.n1 / s.n2;
		double cos_i = vector_dot_product(s.eyev,s.normalv);
		double sin2_t = n_ratio*n_ratio*(1-cos_i*cos_i);

		if (sin2_t >= 1.0)
			return Black;

		//Calculate Refracted Color
		double cos_t = std::sqrt(1.0 - sin2_t);
		
		//Refracted ray direction
		Tuple direction = s.normalv*(n_ratio*cos_i - cos_t) - s.eyev*n_ratio;
		Ray refracted_ray(s.under_point,direction);

		Color refracted_color = w.color_at(refracted_ray, remaining - 1)*transparency;

		//Print out values
		/*
		std::cout << "Remaining: " << remaining << std::endl;
		std::cout << "N1: " << std::setprecision(10) << s.n1 << std::endl;
		std::cout << "N2: "<<std::setprecision(10) << s.n2 << std::endl;
		std::cout << "EYEV: " << s.eyev.x << "," << s.eyev.y << "," << s.eyev.z << std::endl;
		std::cout << "NORMALV: " << s.normalv.x << "," << s.normalv.y << "," << s.normalv.z << std::endl;
		std::cout << "Under Point: " << s.under_point.x << "," << s.under_point.y << "," << s.under_point.z << std::endl;
		std::cout << "N_ratio:" << n_ratio << std::endl;
		std::cout << "cos_i:" << cos_i << std::endl;
		std::cout << "sin2_t:" << sin2_t << std::endl;
		std::cout << "cos_t:" << cos_t << std::endl;
		std::cout << "Refract direction: " << refracted_ray.get_direction().x << "," << refracted_ray.get_direction().y << "," << refracted_ray.get_direction().z << std::endl;
		std::cout << "Refracted color: " << refracted_color.red << "," << refracted_color.green << "," << refracted_color.blue << std::endl;
		std::cout << std::endl;
		*/
			
		return refracted_color;
	}

}


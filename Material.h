#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Canvas.h"
#include "Pattern.h"

namespace RTC
{
	class Color;
	class Light;
	struct ShadeInfo;
	struct World;

	class Material
	{
	public:
		Material();
		Material(const Material& mat);
		virtual ~Material();

		Material& operator=(const Material& rhs);

		virtual Color lighting(std::shared_ptr<Light> light, ShadeInfo& s);
		virtual Color shade_hit(World& w, ShadeInfo& s, int remaining);
		virtual Color reflected_color(World& w, ShadeInfo& s, int remaining);
		virtual Color refracted_color(World& w, ShadeInfo& s, int remaining);

		double get_refractive_index() const;
		void set_reflective(double ref);
		void set_pattern(std::shared_ptr<Pattern> pattern_);
		void set_refractive_index(double ref_i);
		void set_transparency(double trans);

		std::shared_ptr<Pattern> get_pattern();

	protected:
		double reflective, transparency, refractive_index;
		std::shared_ptr<Pattern> pattern;
	};

	class Phong : public Material
	{
	public: 
		Phong();
		Phong(const Phong& mat);
		virtual ~Phong();

		Phong& operator=(const Phong& rhs);

		virtual Color lighting(std::shared_ptr<Light> light, ShadeInfo& s);
		virtual Color reflected_color(World& w, ShadeInfo& s, int remaining);

		void set_ambient(double val);
		void set_diffuse(double val);
		void set_specular(double val);
		void set_shininess(double val);
		void set_color(Color val);

	private:
		double ambient, diffuse, specular, shininess;
		Color color;
	};
}

#endif
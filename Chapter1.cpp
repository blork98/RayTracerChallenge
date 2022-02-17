#include "Chapter1.h"

#include "Canvas.h"
#include <iostream>
#include <fstream>
#include <cmath>

namespace RTC
{
	Projectile::Projectile(const Tuple& vel, const Tuple& pos)
		:velocity(vel), position(pos)
	{}

	Environment::Environment(const Tuple& grav, const Tuple& win)
		:gravity(grav), wind(win)
	{}

	
	Projectile tick(const Environment& env, const Projectile& proj)
	{
		Tuple newPosition = proj.position + proj.velocity;
		Tuple newVelocity = proj.velocity + env.gravity + env.wind;

		return Projectile(newVelocity,newPosition);
	}

	void projectile_test()
	{
		Projectile p(normalize_vector(create_tuple_vector(2.0f,2.0f,0.0f)),create_tuple_point(0.0f,1.0f,0.0f));
		Environment e(create_tuple_vector(0.0f,-0.1f,0.0f),create_tuple_vector(-0.01f,0.0f,0.0f));
		int t = 0;

		while (p.position.y >= 0)
		{
			p = tick(e,p);
			t++;

			std::cout << " Projectile Position at: " << t << std::endl;
			std::cout << " X Pos: " << p.position.x << std::endl;
			std::cout << " Y Pos: " << p.position.y << std::endl;
			std::cout << " Z Pos: " << p.position.z << std::endl;
		}

	}

	void projectile_path_canvas()
	{
		//Create Canvas
		unsigned int w = 900, h = 550;
		Canvas canvas(w, h);

		Tuple startPoint = create_tuple_point(0.0f, 1.0f, 0.0f);
		Tuple velocity = normalize_vector(create_tuple_vector(1.0f,1.8f,0.0f))*11.25;
		Projectile p(velocity, startPoint);

		Tuple gravity = create_tuple_vector(0.0f,-0.1f,0.0f);
		Tuple wind = create_tuple_vector(-0.01f,0.0f,0.0f);
		Environment env(gravity, wind);

		Color color(1.0f, 0.8f, 0.6f);

		canvas(0, 0) = color;

		unsigned int x = 0, y = 0, z = 0;

		while (p.position.y > 0)
		{
			p = tick(env, p);
			x = (int)std::roundf(p.position.x);
			y = (int)std::roundf(p.position.y);

			x = (x > (w - 1)) ? (w - 1) : x;
			y = (y > (h - 1)) ? (h - 1) : y;
			canvas(x, h - y) = color;
		}

		std::ofstream outFile1("PPMProjectile.ppm");
		canvas.write_PPM(outFile1);
		outFile1.close();

	}
	
}


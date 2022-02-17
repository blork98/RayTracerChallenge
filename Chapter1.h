#ifndef CHAPTER1_H_
#define CHAPTER1_H_

#include "Tuple.h"

namespace RTC
{
	struct Projectile
	{
		Projectile(const Tuple& vel, const Tuple& pos);

		Tuple velocity;
		Tuple position;
	};

	struct Environment
	{
		Environment(const Tuple& grav, const Tuple& win);
		Tuple gravity;
		Tuple wind;
	};

	Projectile tick(const Environment& env, const Projectile& proj);

	//Chapter1
	void projectile_test();

	//Chapter2
	void projectile_path_canvas();
}

#endif
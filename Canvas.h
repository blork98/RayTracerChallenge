#ifndef CANVAS_H_
#define CANVAS_H_

#include "Tuple.h"
#include <iostream>
#include<boost/multi_array.hpp>

namespace RTC
{
	class Color
	{
		public:
			Color();
			Color(double r, double g, double b);
			Color(const Color& col);

			Color& operator=(const Color& rhs);

			double& red;
			double& green;
			double& blue;

		private:
			Tuple data;
	};

	Color operator+(const Color& c1, const Color&c2);
	Color operator-(const Color& c1, const Color&c2);
	Color operator*(const Color& c1, const Color&c2);
	Color operator*(double a, const Color&c);
	Color operator*(const Color& c, double a);


	class Canvas
	{
		public:
			Canvas();
			Canvas(unsigned int w, unsigned int h);
			Canvas(const Canvas& c);

			Canvas& operator=(const Canvas& rhs);

			Color& operator()(unsigned int col, unsigned int row);
			const Color& operator()(unsigned int colr, unsigned int row) const;

			void set_all(const Color&c);

			unsigned int get_width() const;
			unsigned int get_height() const;

			void write_PPM(std::ostream& s) const;

		private:
			boost::multi_array<Color,2> data;
			unsigned int width, height;
	};
};

#endif
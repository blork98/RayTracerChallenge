#include "Canvas.h"

namespace RTC
{
	Color::Color()
		:data(Tuple()), red(data.x), green(data.y), blue(data.z)
	{}

	Color::Color(double r, double g, double b)
		:data(Tuple(r,g,b,0.0f)), red(data.x), green(data.y), blue(data.z)
	{}

	Color::Color(const Color& col)
		: data(col.data.x, col.data.y, col.data.z, 0.0f), red(data.x), green(data.y), blue(data.z)
	{}

	Color operator+(const Color& c1, const Color&c2)
	{
		return Color(c1.red+c2.red, c1.green+c2.green,c1.blue+c2.blue);
	}

	Color operator-(const Color& c1, const Color&c2)
	{
		return Color(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue);
	}

	Color operator*(const Color& c1, const Color&c2)
	{
		return Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
	}

	Color operator*(double a, const Color&c)
	{
		return Color(c.red * a, c.green * a, c.blue * a);
	}

	Color operator*(const Color& c, double a)
	{
		return Color(c.red * a, c.green * a, c.blue * a);
	}

	Color& Color::operator=(const Color& rhs)
	{
		if (this == &rhs)
			return (*this);

		red = rhs.red; green = rhs.green; blue = rhs.blue;

		return (*this);
	}

	Canvas::Canvas()
		:width(0), height(0)
	{}

	Canvas::Canvas(unsigned int w, unsigned int h)
		: width(w), height(h), data(boost::multi_array<Color, 2>(boost::extents[h][w]))
	{
		std::fill_n(data.data(),data.num_elements(),Color(0.0f,0.0f,0.0f));

		const boost::multi_array_types::size_type* dims = data.shape();

		if (height != dims[0])
			height = dims[0];

		if (width != dims[1])
			width = dims[1];
	}

	Canvas::Canvas(const Canvas& c)
		: width(c.width), height(c.height), data(c.data)
	{}

	Canvas& Canvas::operator=(const Canvas& rhs)
	{
		if (this == &rhs)
			return (*this);

		height = rhs.height; width = rhs.width; data = rhs.data;

		return (*this);
	}

	Color& Canvas::operator()(unsigned int col, unsigned int row)
	{
		return data[row][col];
	}

	const Color& Canvas::operator()(unsigned int col, unsigned int row) const
	{
		return data[row][col];
	}

	unsigned int Canvas::get_width() const
	{
		return width;
	}

	unsigned int Canvas::get_height() const
	{
		return height;
	}

	void Canvas::set_all(const Color&c)
	{
		for (unsigned int y = 0; y < height; ++y)
			for (unsigned int x = 0; x < width; ++x)
				data[y][x] = c;
	}

	void Canvas::write_PPM(std::ostream& s) const
	{
		s << "P3\n" << width << " " << height << "\n255\n";

		int r, g, b, numDigits;
		unsigned int colCtr = 0;

		for (unsigned int y = 0; y < height; ++y)
		{
			for (unsigned int x = 0; x < width; ++x)
			{

				//if ((x == width - 1) && (y == height - 1))
				//{
				//	Color a = data[y][x];
				//	int c = 0;
				//}

				r = (int)(256.0f * data[y][x].red);
				r = r > 255 ? 255 : r;
				r = r < 0 ? 0 : r;
				if (r > 99)
					numDigits = 3;
				else if (r > 9)
					numDigits = 2;
				else
					numDigits = 1;

				if ((colCtr + numDigits) > 70)
				{
					s << std::endl;
					colCtr = 0;
				}

				s << r << " ";
				colCtr += numDigits;
				colCtr++;
				
				g = (int)(256.0f * data[y][x].green);
				g = g > 255 ? 255 : g;
				g = g < 0 ? 0 : g;
				if (g > 99)
					numDigits = 3;
				else if (g > 9)
					numDigits = 2;
				else
					numDigits = 1;

				if ((colCtr + numDigits) > 70)
				{
					s << std::endl;
					colCtr = 0;
				}

				s << g << " ";
				colCtr += numDigits;
				colCtr++;
				
				b = (int)(256.0f * data[y][x].blue);
				b = b > 255 ? 255 : b;
				b = b < 0 ? 0 : b;
				if (b > 99)
					numDigits = 3;
				else if (b > 9)
					numDigits = 2;
				else
					numDigits = 1;

				if ((colCtr + numDigits) > 70)
				{
					s << std::endl;
					colCtr = 0;
				}
				s << b << " ";
				colCtr += numDigits;
				colCtr++;
				
			}
			s << std::endl;
			colCtr = 0;
		}
	}

}
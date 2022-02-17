#include "CanvasTests.h"
#include "Canvas.h"
#include "Constants.h"
#include <iostream>
#include <fstream>

using namespace RTC;

void canvas_tests()
{
	std::cout << "Canvas Tests:" << std::endl << std::endl;

	test_color();
	test_canvas();

	std::cout << std::endl << std::endl;
}

void test_canvas()
{
	std::cout << "Test Canvas Initialization" << std::endl << std::endl;
	unsigned int h = 20;
	unsigned int w = 10;
	Canvas canvas(w, h);

	if (canvas.get_width() == 10 && canvas.get_height() == 20)
		std::cout << "Width and Height Initialized Correctly: Test Passed" << std::endl;
	else
		std::cout << "Width and Height not Initialzed Correctly: Test Failed" << std::endl;

	bool errorPresent = false;
	
	for (unsigned int y = 0; y < h; ++y)
	{
		for (unsigned int x = 0; x < w; ++x)
		{
			if (!(essentially_equal(0.0f, canvas(x, y).red) && essentially_equal(0.0f, canvas(x, y).green) && essentially_equal(0.0f, canvas(x, y).blue)))
			{
				std::cout << "Position x: " << x << " and y: " << y << " does not have value C(0,0,0): Test Failed" << std::endl;
				errorPresent = true;
				break;
			}

		}
		
		if (errorPresent)
			break;
	}

	if(!errorPresent)
		std::cout << "Every Pixel has value (0,0,0): Test Passed" << std::endl;

	//Test assignment
	canvas(2, 3) = Color(1.0f, 0.0f, 0.0f);
	Color a = canvas(2, 3);
	
	if (essentially_equal(1.0f, canvas(2, 3).red) && essentially_equal(0.0f, canvas(2, 3).green) && essentially_equal(0.0f, canvas(2, 3).blue))
		std::cout << "Pixel(2,3) has value C(1,0,0): Test Passed" << std::endl;
	else
		std::cout << "Pixel(2,3) does not have value C(1,0,0): Test Failed" << std::endl;

	//Test PPM1
	std::ofstream outFile("PPMTest1.ppm");
	Canvas c1(5,3);
	c1(0, 0) = Color(1.5f,0.0f,0.0f);
	c1(2, 1) = Color(0.0f,0.5f,0.0f);
	c1(4, 2) = Color(-0.5f,0.0f,1.0f);

	c1.write_PPM(outFile);
	outFile.close();

	//Test PPm2
	std::ofstream outFile1("PPMTest2.ppm");
	Canvas c2(10,2);
	c2.set_all(Color(1.0f,0.8f,0.6f));
	c2.write_PPM(outFile1);
	outFile1.close();

	std::cout << "View PPM files to check test" << std::endl;

	std::cout << std::endl;
}

void test_color()
{
	std::cout << "Test Color" << std::endl << std::endl;


	//Initialization
	Color c(-0.5f, 0.4f, 1.7f);

	if (essentially_equal(-0.5f, c.red) && essentially_equal(0.4f, c.green) && essentially_equal(1.7f, c.blue))
		std::cout << "Color initialization passed" << std::endl;

	//Test Addition
	Color c1(0.9f,0.6f,0.75f);
	Color c2(0.7f,0.1f,0.25f);
	Color c3 = c1 + c2;
	if (essentially_equal(1.6f, c3.red) && essentially_equal(0.7f, c3.green) && essentially_equal(1.0f, c3.blue))
		std::cout << "C(0.9,0.6,0.75) + C(0.7,0.1,0.25,1,0) is C(1.6,0.7,1.0): Color Addition Test Passed" << std::endl;
	else
		std::cout << "Color Addition Test Failed" << std::endl;

	//Test Subtraction
	Color c4 = c1 - c2;
	if (essentially_equal(0.2f, c4.red) && essentially_equal(0.5f, c4.green) && essentially_equal(0.5f, c4.blue))
		std::cout << "C(0.9,0.6,0.75) - C(0.7,0.1,0.25,1,0) is C(0.2,0.5,0.5): Color Subtraction Test Passed" << std::endl;
	else
		std::cout << "Color Subtraction Test Failed" << std::endl;

	//Test scalar multiplication
	Color c5 = Color(0.2f,0.3f,0.4f);
	Color c6 = 2.0f*c5;
	if (essentially_equal(0.4f, c6.red) && essentially_equal(0.6f, c6.green) && essentially_equal(0.8f, c6.blue))
		std::cout << "C(1.0,0.2,0.4)*2 is C(2.0,0.4,0.8): Color Scalar Mult Test Passed" << std::endl;
	else
		std::cout << "Color Scalar Mult Test Failed" << std::endl;

	//Test color multiplication
	Color c7 = Color(1.0f, 0.2f, 0.4f);
	Color c8 = Color(0.9f, 1.0f, 0.1f);
	Color c9 = c7*c8;
	if (essentially_equal(0.9f, c9.red) && essentially_equal(0.2f, c9.green) && essentially_equal(0.04f, c9.blue))
		std::cout << "C(1.0,0.2,0.4)*C(0.9,1.0,0.1) is C(0.9,0.2,0.04): Color Mult Test Passed" << std::endl;
	else
		std::cout << "Color Mult Test Failed" << std::endl;

	std::cout << std::endl;
}


#ifndef CANVASTESTS_H_
#define CANVASTESTS_H_

void canvas_tests();

//Scenario: Colors are(red, green, blue) tuples
//	Given c ? color(-0.5, 0.4, 1.7)
//	Then c.red = -0.5
//	And c.green = 0.4
//	And c.blue = 1.7

//Scenario: Adding colors
//	Given c1 ? color(0.9, 0.6, 0.75)
//	And c2 ? color(0.7, 0.1, 0.25)
//	Then c1 + c2 = color(1.6, 0.7, 1.0)
	
//Scenario : Subtracting colors
//	Given c1 ? color(0.9, 0.6, 0.75)
//	And c2 ? color(0.7, 0.1, 0.25)
//	Then c1 - c2 = color(0.2, 0.5, 0.5)

//Scenario : Multiplying a color by a scalar
//	Given c ? color(0.2, 0.3, 0.4)
//	Then c * 2 = color(0.4, 0.6, 0.8)

//Scenario: Multiplying colors
//	Given c1 ? color(1, 0.2, 0.4)
//	And c2 ? color(0.9, 1, 0.1)
//	Then c1 * c2 = color(0.9, 0.2, 0.04)

void test_color();

//Scenario: Creating a canvas
//	Given c ? canvas(10, 20)
//	Then c.width = 10
//	And c.height = 20
//	And every pixel of c is color(0, 0, 0)

//Scenario: Writing pixels to a canvas
//	Given c ? canvas(10, 20)
//	And red ? color(1, 0, 0)
//	When write_pixel(c, 2, 3, red)
//	Then pixel_at(c, 2, 3) = red

//Scenario: Constructing the PPM header
//	Given c ? canvas(5, 3)
//	When ppm ? canvas_to_ppm(c)
//	Then lines 1 - 3 of ppm are
//	"""
//	P3
//	5 3
//	255
//	"""

void test_canvas();



#endif
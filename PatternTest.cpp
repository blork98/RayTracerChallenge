#include "PatternTest.h"
#include "Pattern.h"
#include "Constants.h"
#include "Light.h"
#include "Material.h"
#include "GeometricObject.h"
#include "Transform.h"


#include <iostream>

using namespace RTC;

class TestPattern : public Pattern
{
	public:	
		Color pattern_at(Tuple point) const
		{
			return Color(point.x,point.y,point.z);
		}
};

void pattern_tests()
{
	std::cout << "Pattern Tests:" << std::endl << std::endl;

	test_pattern();
	test_material_pattern();
	test_pattern_transformation();
	test_general_pattern_trans();
	test_various_patterns();

	std::cout << std::endl << std::endl;
}

void test_various_patterns()
{
	//Gradient Pattern
	GradientPattern grad(White, Black);
	Color c1 = grad.pattern_at(create_tuple_point(0,0,0));
	Color c2 = grad.pattern_at(create_tuple_point(0.25, 0.0, 0.0));
	Color c3 = grad.pattern_at(create_tuple_point(0.5, 0.0, 0.0));
	Color c4 = grad.pattern_at(create_tuple_point(0.75, 0.0, 0.0));

	bool test1 = floatCompareSpecified(c1.red, 1.0,0.00001) && floatCompareSpecified(c1.green, 1.0, 0.00001) && floatCompareSpecified(c1.blue, 1.0, 0.00001);
	bool test2 = floatCompareSpecified(c2.red, 0.75, 0.00001) && floatCompareSpecified(c2.green, 0.75, 0.00001) && floatCompareSpecified(c2.blue, 0.75, 0.00001);
	bool test3 = floatCompareSpecified(c3.red, 0.5, 0.00001) && floatCompareSpecified(c3.green, 0.5, 0.00001) && floatCompareSpecified(c3.blue, 0.5, 0.00001);
	bool test4 = floatCompareSpecified(c4.red, 0.25, 0.00001) && floatCompareSpecified(c4.green, 0.25, 0.00001) && floatCompareSpecified(c4.blue, 0.25, 0.00001);

	if (test1&&test2&&test3&&test4)
		std::cout << "Gradient Pattern: Test passed" << std::endl;
	else
		std::cout << "Gradient Pattern: Test failed" << std::endl;

	//Ring Pattern
	RingPattern ring(White, Black);
	c1 = ring.pattern_at(create_tuple_point(0, 0, 0));
	c2 = ring.pattern_at(create_tuple_point(1.0, 0.0, 0.0));
	c3 = ring.pattern_at(create_tuple_point(0.0, 0.0, 1.0));
	c4 = ring.pattern_at(create_tuple_point(0.708, 0.0, 0.708));

	test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);
	test2 = essentially_equal(Black.red, c2.red) && essentially_equal(Black.green, c2.green) && essentially_equal(Black.blue, c2.blue);
	test3 = essentially_equal(Black.red, c3.red) && essentially_equal(Black.green, c3.green) && essentially_equal(Black.blue, c3.blue);
	test4 = essentially_equal(Black.red, c4.red) && essentially_equal(Black.green, c4.green) && essentially_equal(Black.blue, c4.blue);

	if (test1&&test2&&test3&&test4)
		std::cout << "Ring Pattern: Test passed" << std::endl;
	else
		std::cout << "Ring Pattern: Test failed" << std::endl;

	//Checker Pattern
	//Checker Repeats in x
	CheckerPattern check1(White, Black);
	c1 = check1.pattern_at(create_tuple_point(0, 0, 0));
	c2 = check1.pattern_at(create_tuple_point(0.99, 0.0, 0.0));
	c3 = check1.pattern_at(create_tuple_point(1.01, 0.0, 0.0));
	test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);
	test2 = essentially_equal(White.red, c2.red) && essentially_equal(White.green, c2.green) && essentially_equal(White.blue, c2.blue);
	test3 = essentially_equal(Black.red, c3.red) && essentially_equal(Black.green, c3.green) && essentially_equal(Black.blue, c3.blue);

	if (test1&&test2&&test3)
		std::cout << "Checker Pattern Repeats in X: Test passed" << std::endl;
	else
		std::cout << "Checker Pattern Repeats in X: Test failed" << std::endl;
	
	//Checker Patern Repeats in y
	c1 = check1.pattern_at(create_tuple_point(0, 0, 0));
	c2 = check1.pattern_at(create_tuple_point(0.0, 0.99, 0.0));
	c3 = check1.pattern_at(create_tuple_point(0.00, 1.01, 0.0));
	test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);
	test2 = essentially_equal(White.red, c2.red) && essentially_equal(White.green, c2.green) && essentially_equal(White.blue, c2.blue);
	test3 = essentially_equal(Black.red, c3.red) && essentially_equal(Black.green, c3.green) && essentially_equal(Black.blue, c3.blue);

	if (test1&&test2&&test3)
		std::cout << "Checker Pattern Repeats in Y: Test passed" << std::endl;
	else
		std::cout << "Checker Pattern Repeats in Y: Test failed" << std::endl;

	//Checkr Pattern Repeats in z
	c1 = check1.pattern_at(create_tuple_point(0, 0, 0));
	c2 = check1.pattern_at(create_tuple_point(0.0, 0.0, 0.99));
	c3 = check1.pattern_at(create_tuple_point(0.00, 0.00, 1.01));
	test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);
	test2 = essentially_equal(White.red, c2.red) && essentially_equal(White.green, c2.green) && essentially_equal(White.blue, c2.blue);
	test3 = essentially_equal(Black.red, c3.red) && essentially_equal(Black.green, c3.green) && essentially_equal(Black.blue, c3.blue);

	if (test1&&test2&&test3)
		std::cout << "Checker Pattern Repeats in Z: Test passed" << std::endl;
	else
		std::cout << "Checker Pattern Repeats in Z: Test failed" << std::endl;

	std::cout << std::endl;
}

void test_general_pattern_trans()
{
	ShadeInfo s;

	//Test Pattern with Object Transformation
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->set_transform(std::make_shared<Scaling>(2.0, 2.0, 2.0));
	std::shared_ptr<Pattern> pattern = std::make_shared<TestPattern>();
	sphere->get_material()->set_pattern(pattern);
	s.object = sphere;
	Color c1 = sphere->get_material()->get_pattern()->pattern_at_object(create_tuple_point(2.0,3.0,4.0),s);
	bool test1 = essentially_equal(1.0, c1.red) && essentially_equal(1.5, c1.green) && essentially_equal(2.0, c1.blue);
	if (test1)
		std::cout << "Pattern with an Object Transformation: Test passed" << std::endl;
	else
		std::cout << "Pattern with an Object Transformation: Test failed" << std::endl;

	//Test Pattern with Pattern Transformation
	s.object = std::make_shared<Sphere>();
	TestPattern pattern1;
	pattern1.set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));
	Color c2 = pattern1.pattern_at_object(create_tuple_point(2.0, 3.0, 4.0), s);
	bool test2 = essentially_equal(1.0, c2.red) && essentially_equal(1.5, c2.green) && essentially_equal(2.0, c2.blue);
	if (test2)
		std::cout << "Pattern with Pattern Transformation: Test passed" << std::endl;
	else
		std::cout << "Pattern with Pattern Transformation: Test failed" << std::endl;

	//Pattern with Object and Pattern Transformation
	sphere->set_transform(std::make_shared<Scaling>(2.0, 2.0, 2.0));
	std::shared_ptr<TestPattern> pattern3 = std::make_shared<TestPattern>();
	pattern3->set_transform(std::make_shared<Translation>(0.5,1.0,1.5));
	sphere->get_material()->set_pattern(pattern3);
	s.object = sphere;
	Color c3 = sphere->get_material()->get_pattern()->pattern_at_object(create_tuple_point(2.5, 3.0, 3.5), s);
	bool test3 = essentially_equal(0.75, c3.red) && essentially_equal(0.5, c3.green) && essentially_equal(0.25, c3.blue);
	if (test3)
		std::cout << "Pattern with Object & Pattern Transformation: Test passed" << std::endl;
	else
		std::cout << "Pattern with  Object & Pattern Transformation: Test failed" << std::endl;

	std::cout << std::endl;
}

void test_pattern_transformation()
{
	//Strip with object Transformation
	StripePattern pattern(White, Black);
	std::shared_ptr<GeometricObject> sphere = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	sphere->set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));

	ShadeInfo s;
	s.object = sphere;
	Color c1 = pattern.pattern_at_object(create_tuple_point(1.5,0.0,0.0), s);
	bool test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);

	if (test1)
		std::cout << "Stripes with an Object Transformation: Test passed" << std::endl;
	else
		std::cout << "Stripes with an Object Transformation: Test failed" << std::endl;

	//Stripe with Pattern Transform
	sphere = std::make_shared<Sphere>(create_tuple_point(0.0f, 0.0f, 0.0f), 1.0f);
	s.object = sphere;
	pattern.set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));
	Color c2 = pattern.pattern_at_object(create_tuple_point(1.5, 0.0, 0.0), s);
	bool test2 = essentially_equal(White.red, c2.red) && essentially_equal(White.green, c2.green) && essentially_equal(White.blue, c2.blue);

	if (test2)
		std::cout << "Stripes with an Pattern Transformation: Test passed" << std::endl;
	else
		std::cout << "Stripes with an Pattern Transformation: Test failed" << std::endl;

	//Stripe with Object and Pattern Transform
	pattern.set_transform(std::make_shared<Translation>(0.5,0.0,0.0));
	sphere->set_transform(std::make_shared<Scaling>(2.0,2.0,2.0));
	s.object = sphere;
	Color c3 = pattern.pattern_at_object(create_tuple_point(2.5, 0.0, 0.0), s);
	bool test3 = essentially_equal(White.red, c3.red) && essentially_equal(White.green, c3.green) && essentially_equal(White.blue, c3.blue);

	if (test3)
		std::cout << "Stripes with an Pattern and Object Transformation: Test passed" << std::endl;
	else
		std::cout << "Stripes with an Pattern and Object Transformation: Test failed" << std::endl;

	std::cout << std::endl;
}

void test_material_pattern()
{
	//Test Lighting with Pattern
	std::shared_ptr<Light> light = std::make_shared<PointLight>(create_tuple_point(0.0f, 0.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
	Phong material;
	material.set_ambient(1.0);
	material.set_diffuse(0.0);
	material.set_specular(0.0);
	material.set_pattern(std::make_shared<StripePattern>(White, Black));

	ShadeInfo s;
	s.object = std::make_shared<Sphere>();
	s.eyev = create_tuple_vector(0.0, 0.0, -1.0);
	s.normalv = create_tuple_vector(0.0, 0.0, -1.0);
	s.hit_point = create_tuple_point(0.9,0.0,0.0);
	s.in_shadow = false;
	Color c1 = material.lighting(light, s);
	s.hit_point = create_tuple_point(1.1, 0.0, 0.0);
	Color c2 = material.lighting(light, s);

	bool test1 = essentially_equal(White.red, c1.red) && essentially_equal(White.green, c1.green) && essentially_equal(White.blue, c1.blue);
	bool test2 = essentially_equal(Black.red, c2.red) && essentially_equal(Black.green, c2.green) && essentially_equal(Black.blue, c2.blue);

	if (test1&&test2)
		std::cout << "Lighting with Pattern: Test passed" << std::endl;
	else
		std::cout << "Lighting with Pattern: Test failed" << std::endl;

	std::cout << std::endl;
}

void test_pattern()
{
	//Test Initialization
	StripePattern pattern(White, Black);
	
	//Pattern is constant in y
	Color cy;
	cy = pattern.pattern_at(create_tuple_point(0.0,0.0,0.0));
	bool test1 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(0.0, 1.0, 0.0));
	bool test2 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(0.0,2.0,0.0));
	bool test3 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);

	if (test1&&test2&&test3)
		std::cout << "Strip Pattern Constant in y: Test passed" << std::endl;
	else
		std::cout << "Strip Pattern Constant in y: Test failed" << std::endl;

	//Pattern is constant in z
	cy = pattern.pattern_at(create_tuple_point(0.0, 0.0, 0.0));
	test1 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(0.0, 0.0, 1.0));
	test2 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(0.0, 0.0, 2.0));
	test3 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);

	if (test1&&test2&&test3)
		std::cout << "Strip Pattern Constant in z: Test passed" << std::endl;
	else
		std::cout << "Strip Pattern Constant in z: Test failed" << std::endl;

	//Pattern alternates in x
	cy = pattern.pattern_at(create_tuple_point(0.0, 0.0, 0.0));
	test1 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(0.9, 0.0, 0.0));
	test2 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(1.0, 0.0, 0.0));
	test3 = essentially_equal(Black.red, cy.red) && essentially_equal(Black.green, cy.green) && essentially_equal(Black.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(-0.1, 0.0, 0.0));
	bool test4 = essentially_equal(Black.red, cy.red) && essentially_equal(Black.green, cy.green) && essentially_equal(Black.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(-1.0, 0.0, 0.0));
	bool test5 = essentially_equal(Black.red, cy.red) && essentially_equal(Black.green, cy.green) && essentially_equal(Black.blue, cy.blue);
	cy = pattern.pattern_at(create_tuple_point(-1.1, 0.0, 0.0));
	bool test6 = essentially_equal(White.red, cy.red) && essentially_equal(White.green, cy.green) && essentially_equal(White.blue, cy.blue);

	if (test1&&test2&&test3&&test4&&test5&&test6)
		std::cout << "Strip Pattern Alternates in x: Test passed" << std::endl;
	else
		std::cout << "Strip Pattern Alternates in x: Test failed" << std::endl;

	std::cout << std::endl << std::endl;
}


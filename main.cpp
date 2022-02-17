#include "TupleTests.h"
#include "CanvasTests.h"
#include "MatrixTests.h"
#include "Chapter1.h"
#include "TransformTests.h"
#include "RaySphereIntersection.h"
#include "Chapter5.h"
#include "LightShading.h"
#include "SceneCreation.h"
#include "ShadowTests.h"
#include "PlaneTests.h"
#include "PatternTest.h"
#include "ReflectionRefractionTests.h"

int main()
{
	//tuple_tests();
	//RTC::projectile_test();
	//RTC::projectile_path_canvas();
	//canvas_tests();
	//matrix_tests();
	//transform_tests();
	//ray_sphere_intersection_tests();
	//RTC::draw_red_sphere();
	//light_and_shading_tests();
	//RTC::render_phong_sphere();
	//RTC::scene_tests();
	//RTC::render_multi_sphere();
	//shadow_tests();
	//plane_tests();
	//RTC::render_sphere_plane();
	//pattern_tests();
	//RTC::render_patterns();
	//reflection_refraction_tests();
	//RTC::render_reflection_test();
	RTC::render_refraction_transparency();

 	return 0;
}
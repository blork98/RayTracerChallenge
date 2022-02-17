#ifndef LIGHTSHADING_H_
#define LIGHTSHADING_H_

void light_and_shading_tests();

//Scenario: The normal on a sphere at a point on the x axis
//	Given s ? sphere()
//	When n ? normal_at(s, point(1, 0, 0))
//	Then n = vector(1, 0, 0)

//Scenario: The normal on a sphere at a point on the y axis
//	Given s ? sphere()
//	When n ? normal_at(s, point(0, 1, 0))
//	Then n = vector(0, 1, 0)

//Scenario: The normal on a sphere at a point on the z axis
//	Given s ? sphere()
//	When n ? normal_at(s, point(0, 0, 1))
//	Then n = vector(0, 0, 1)

//Scenario: The normal on a sphere at a nonaxial point
//	Given s ? sphere()
//	When n ? normal_at(s, point(?3 / 3, ?3 / 3, ?3 / 3))
//	Then n = vector(?3 / 3, ?3 / 3, ?3 / 3)

//Scenario: The normal is a normalized vector
//	Given s ? sphere()
//	When n ? normal_at(s, point(?3 / 3, ?3 / 3, ?3 / 3))
//	Then n = normalize(n)

//Scenario: Computing the normal on a translated sphere
//	Given s ? sphere()
//	And set_transform(s, translation(0, 1, 0))
//	When n ? normal_at(s, point(0, 1.70711, -0.70711))
//	Then n = vector(0, 0.70711, -0.70711)

//Scenario : Computing the normal on a transformed sphere
//	Given s ? sphere()
//	And m ? scaling(1, 0.5, 1) * rotation_z(? / 5)
//	And set_transform(s, m)
//	When n ? normal_at(s, point(0, ?2 / 2, -?2 / 2))
//	Then n = vector(0, 0.97014, -0.24254)

void test_normals();

//Scenario: Reflecting a vector approaching at 45°
//	Given v ? vector(1, -1, 0)
//	And n ? vector(0, 1, 0)
//	When r ? reflect(v, n)
//	Then r = vector(1, 1, 0)

//Scenario: Reflecting a vector off a slanted surface
//	Given v ? vector(0, -1, 0)
//	And n ? vector(?2 / 2, ?2 / 2, 0)
//	When r ? reflect(v, n)
//	Then r = vector(1, 0, 0)

void test_reflection();

//Scenario: A point light has a position and intensity
//	Given intensity ? color(1, 1, 1)
//	And position ? point(0, 0, 0)
//	When light ? point_light(position, intensity)
//	Then light.position = position
//	And light.intensity = intensity
void test_color_material();

//Background:
//Given m ? material()
//And position ? point(0, 0, 0)

//Scenario: Lighting with the eye between the light and the surface
//	Given eyev ? vector(0, 0, -1)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 0, -10), color(1, 1, 1))
//	When result ? lighting(m, light, position, eyev, normalv)
//	Then result = color(1.9, 1.9, 1.9)

//Scenario: Lighting with the eye between light and surface, eye offset 45°
//	Given eyev ? vector(0, ?2 / 2, -?2 / 2)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 0, -10), color(1, 1, 1))
//	When result ? lighting(m, light, position, eyev, normalv)
//	Then result = color(1.0, 1.0, 1.0)

//Scenario: Lighting with eye opposite surface, light offset 45°
//	Given eyev ? vector(0, 0, -1)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 10, -10), color(1, 1, 1))
//	When result ? lighting(m, light, position, eyev, normalv)
//	Then result = color(0.7364, 0.7364, 0.7364)

//Scenario: Lighting with eye in the path of the reflection vector
//	Given eyev ? vector(0, -?2 / 2, -?2 / 2)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 10, -10), color(1, 1, 1))
//	When result ? lighting(m, light, position, eyev, normalv)
//	Then result = color(1.6364, 1.6364, 1.6364)

//Scenario: Lighting with the light behind the surface
//	Given eyev ? vector(0, 0, -1)
//	And normalv ? vector(0, 0, -1)
//	And light ? point_light(point(0, 0, 10), color(1, 1, 1))
//	When result ? lighting(m, light, position, eyev, normalv)
//	Then result = color(0.1, 0.1, 0.1)

void test_material_lighting();

#endif
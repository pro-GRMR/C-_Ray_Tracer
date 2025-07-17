#include <iostream>
#include "shapes.hpp"
#include "scene.hpp"

int main()
{
    Vector c_pos = Vector(0, 0, 10);
    Vector l_pos = Vector(100, 100, -100);
    Color back = Color(80, 91, 2.1);

    float s_refl = 0.8;
    Color s_col = Color(1.1, 201.2, 9.1);
    Vector center = Vector(1, 1, 1);
    double radius = 1;
    std::shared_ptr<Shape> sphere(new Sphere(s_col, s_refl, center, radius));

    float p_refl = 0.2;
    Color p_col = Color(0, 0, 101);
    Vector point = Vector(2, 2, 2);
    Vector norm = Vector(1, 0, 0);
    std::shared_ptr<Shape> plane(new Plane(p_col, p_refl, point, norm));

    double l_ambient = 0.9;
    double l_diffuse = 0.1;
    unsigned l_specular = 10;
    unsigned l_reflected = 9;

    Scene scene1 = Scene(c_pos, l_pos, l_ambient, l_diffuse, l_specular, l_reflected, back);
    scene1.add_shape(plane);
    scene1.add_shape(sphere);

    Vector point2 = Vector(10, 10, 10);
    Color point_color = scene1.compute_point_color(point2);
    double red = point_color.get_r();
    double green = point_color.get_g();
    double blue = point_color.get_b();

    std::cout << "Point color (should be 80, 91, 2.1): " << red << ", " << green << ", " << blue << std::endl;

    Scene scene2 = Scene(c_pos, l_pos);
    point_color = scene2.compute_point_color(point2);
    red = point_color.get_r();
    green = point_color.get_g();
    blue = point_color.get_b();

    std::cout << "Point color (should be 135, 206, 235): " << red << ", " << green << ", " << blue << std::endl;
}
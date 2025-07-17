#include "shapes.hpp"
#include <cmath>
#include <algorithm>

Shape::Shape(Color col, double ref) : color(col), reflectivity(ref) {}
Shape::~Shape() {}

double Shape::get_reflectivity() const
{
    return reflectivity;
}
Color Shape::get_color() const
{
    return color;
}

Sphere::Sphere(Color col, double ref, Vector cen, double r) : Shape::Shape(col, ref), center(cen), radius(r) {}
Sphere::~Sphere() {}
double Sphere::get_collision_time(Ray r) const
{
    Vector s = r.get_start(), d = r.get_direction();
    double a = d.dot_product(d);
    double b = 2 * d.dot_product(s - center);
    double c = (s - center).dot_product(s - center) - radius * radius;

    double det = b * b - 4 * a * c;
    double t1 = (-b + sqrt(det)) / (2 * a);
    double t2 = (-b - sqrt(det)) / (2 * a);

    if (det < 0 || (t1 < 0 && t2 < 0))
    {
        return -1;
    }
    else if (t1 < 0)
    {
        return t2;
    }
    else if (t2 < 0)
    {
        return t1;
    }
    else
    {
        return std::min(t1, t2);
    }
}
Vector Sphere::get_normal_vector(Vector s) const
{
    return s - center;
}

Plane::Plane(Color col, double ref, Vector p, Vector n) : Shape::Shape(col, ref), point(p), normal(n) {}
Plane::~Plane() {}
double Plane::get_collision_time(Ray r) const
{
    Vector s = r.get_start(), d = r.get_direction();
    double dn = normal.dot_product(d);

    if (dn < 1e-6 && dn > -1e-6)
    {
        return -1;
    }
    else
    {
        return normal.dot_product(point - s) / dn;
    }
}
Vector Plane::get_normal_vector(Vector s) const
{
    return 0 * s + normal;
}
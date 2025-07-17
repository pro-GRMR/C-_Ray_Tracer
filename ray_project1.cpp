#include <iostream>
#include <string>
#include "ray_project1.hpp"
#include <cmath>

Vector::Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

double Vector::dot_product(Vector u) const
{
    return (x * u.x + y * u.y + z * u.z);
}

double Vector::magnitude() const
{
    return sqrt(dot_product(*this));
}
Vector Vector::project(Vector u) const
{
    return (dot_product(u)) / (u.dot_product(u)) * u;
}
Vector Vector::normalized() const{
    return 1 / magnitude() * (*this);
}


Vector Vector::operator-(Vector u) const
{
    return Vector(x - u.x, y - u.y, z - u.z);
}
Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

Vector Vector::operator+(Vector u) const
{
    return Vector(x + u.x, y + u.y, z + u.z);
}

Vector operator*(double c, Vector v)
{
    return Vector(c * v.x, c * v.y, c * v.z);
}

Ray::Ray(Vector start, Vector direction) : strt(start), dir(direction) {}

Vector Ray::get_start() const
{
    return strt;
}
Vector Ray::get_direction() const
{
    return dir;
}

Color::Color() : r(0), g(0), b(0) {}

Color::Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}

double Color::get_r() const
{
    return r;
}

double Color::get_g() const
{
    return g;
}

double Color::get_b() const
{
    return b;
}

Color Color::operator+(Color c) const
{
    return Color(r + c.r, g + c.g, b + c.b);
}

void Color::operator+=(Color c)
{
    r += c.r;
    g += c.g;
    b += c.b;
}

Color operator*(double c, Color v)
{
    return Color(c * v.r, c * v.g, c * v.b);
}

bool Vector::operator==(const Vector &v) const
{
    return std::abs(x - v.x) < 1e-6 &&
           std::abs(y - v.y) < 1e-6 &&
           std::abs(z - v.z) < 1e-6;
}

bool Ray::operator==(const Ray &r) const
{
    return strt == r.strt && dir == r.dir;
}

bool Color::operator==(const Color &c) const
{
    return std::abs(r - c.r) < 1e-6 &&
           std::abs(g - c.g) < 1e-6 &&
           std::abs(b - c.b) < 1e-6;
}

Vector::~Vector() {}
Ray::~Ray() {}
Color::~Color() {}
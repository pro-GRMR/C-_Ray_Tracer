#pragma once
#include <iostream>

class Vector
{
private:
    double x;
    double y;
    double z;

public:
    Vector(double, double, double);

    double dot_product(Vector) const;
    double magnitude() const;
    Vector project(Vector) const;
    Vector normalized() const;

    Vector operator-(Vector) const;
    Vector operator-() const;
    Vector operator+(Vector) const;

    friend Vector operator*(double, Vector);

    bool operator==(const Vector& v) const;
    ~Vector();
};

class Ray
{
private:
    Vector strt, dir;
public:
    Ray(Vector, Vector);
    Vector get_start() const;
    Vector get_direction() const;

    bool operator==(const Ray& r) const;
    ~Ray();
};

class Color
{
private:
    double r, g, b;

public:
    Color();
    Color(double, double, double);
    double get_r() const;
    double get_g() const;
    double get_b() const;
    Color operator+(Color) const;
    void operator+=(Color);
    friend Color operator*(double, Color);

    bool operator==(const Color& c) const;
    ~Color();
};


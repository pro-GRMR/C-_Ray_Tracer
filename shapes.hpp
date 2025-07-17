#pragma once
#include "ray_project1.hpp"
class Shape
{
private:
    Color color;
    double reflectivity;

public:
    Shape(Color, double);
    virtual ~Shape();
    virtual double get_collision_time(Ray) const = 0;
    virtual Vector get_normal_vector(Vector) const = 0;
    Color get_color() const;
    double get_reflectivity() const;
};

class Sphere : public Shape
{
private:
    Vector center;
    double radius;

public:
    Sphere(Color, double, Vector, double);
    ~Sphere();
    double get_collision_time(Ray) const override;
    Vector get_normal_vector(Vector) const override;
};

class Plane : public Shape
{
private:
    Vector point;
    Vector normal;
public:
    Plane(Color, double, Vector, Vector);
    ~Plane();
    double get_collision_time(Ray) const override;
    Vector get_normal_vector(Vector) const override;
};
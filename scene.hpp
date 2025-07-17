#pragma once
#include "ray_project1.hpp"
#include "shapes.hpp"
class Scene
{
private:
    Vector camera, light_source;
    double ambient, specular, sp;
    unsigned max_refl;
    Color background;
    std::vector<std::shared_ptr<Shape>> Shapes;
    std::pair<int, double> find_intersect_index(Ray) const;
    Color get_ray_color(Ray, int) const;

public:
    Scene(Vector, Vector, double, double, double, unsigned, Color);
    Scene(Vector, Vector);
    ~Scene();
    void add_shape(std::shared_ptr<Shape>);

    Color compute_point_color(Vector) const;
};
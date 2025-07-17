#include "scene.hpp"

#include <algorithm>

#include <cmath>

#include <limits>

Scene::Scene(Vector cam, Vector light, double ambient_factor, double specular_factor, double specular_exponent, unsigned max_reflection, Color backgr)

    : camera(cam), light_source(light), ambient(ambient_factor), specular(specular_factor), sp(specular_exponent), max_refl(max_reflection), background(backgr)

{

    Shapes = {};
}

Scene::Scene(Vector cam, Vector light) : camera(cam), light_source(light), ambient(0.2), specular(0.5), sp(8), max_refl(6), background(Color(135, 206, 235))

{

    Shapes = {};
}

Scene::~Scene() {}

void Scene::add_shape(std::shared_ptr<Shape> s)

{

    Shapes.push_back(s);
}

std::pair<int, double> Scene::find_intersect_index(Ray r) const

{

    double min_time = std::numeric_limits<double>::infinity();

    int index = -1;

    for (unsigned i = 0; i < Shapes.size(); i++)

    {

        double time = Shapes[i]->get_collision_time(r);

        if (time > 0 && time < min_time)

        {

            min_time = time;

            index = i;
        }
    }

    return std::make_pair(index, min_time);
}

Color Scene::get_ray_color(Ray r, int refl_left) const

{

    r = Ray(r.get_start() + 1e-6 * r.get_direction(), r.get_direction());

    auto p = find_intersect_index(r);

    if (p.first == -1)

    {

        return background;
    }

    auto o = Shapes[p.first];

    Vector d = r.get_direction();

    Vector s = r.get_start();

    Vector v = 1 / d.magnitude() * d;

    Vector i = s + p.second * d;

    Vector n = o->get_normal_vector(i);

    Vector lt = light_source - i;

    // Normalize

    n = 1 / n.magnitude() * n;

    lt = 1 / lt.magnitude() * lt;

    // Shadow ray check

    Ray shadow_ray(i + 1e-6 * n, lt);

    auto shadow_hit = find_intersect_index(shadow_ray);

    bool in_shadow = false;

    if (shadow_hit.first != -1)
    {

        if (shadow_hit.second  < (light_source - i).magnitude())
        {

            in_shadow = true;
        }
    }

    double a = ambient * (1 - o->get_reflectivity());

    Color l_ambient = a * o->get_color();

    Color l_diffuse = Color(0, 0, 0);

    Color l_specular = Color(0, 0, 0);

    if (!in_shadow)
    {

        l_diffuse = (1 - a) * (1 - o->get_reflectivity()) * std::max(0.0, n.dot_product(lt)) * o->get_color();

        Vector h = lt - v;

        h = 1 / h.magnitude() * h;

        l_specular = specular * std::pow(std::max(0.0, h.dot_product(n)), sp) * Color(255, 255, 255) ;
    }

    Color l_reflected = Color(0, 0, 0);

    if (refl_left > 0)

    {

        Vector refl = v - 2 * v.project(n);

        Color c = get_ray_color(Ray(i, refl), refl_left - 1);

        l_reflected = (1 - a) * o->get_reflectivity() * c;
    }

    return (l_ambient + l_diffuse + l_specular + l_reflected);
}

Color Scene::compute_point_color(Vector p) const
{

    return get_ray_color(Ray(camera, p - camera), max_refl);
}

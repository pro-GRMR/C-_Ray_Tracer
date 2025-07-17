#include <iostream>
#include <cassert>
#include "ray_project1.hpp"

// Test function for Vector class
void test_vector()
{
    Vector unit_x = Vector(1, 0, 0);
    Vector unit_y = Vector(0, 1, 0);
    Vector unit_z = Vector(0, 0, 1);

    Vector v = Vector(1.2, 0.64, -101.875);

    // Test dot product
    assert(unit_x.dot_product(unit_y) == 0); // should be 0
    assert(v.dot_product(unit_y) == 0.64);   // should be 0.64

    // Test magnitude
    assert(unit_x.magnitude() == 1); // should be 1

    // Test projection
    Vector v_x = v.project(unit_x); // should be Vector(1.2, 0, 0)
    assert(v_x == Vector(1.2, 0, 0));

    // Test vector operations
    Vector add = unit_x + unit_y; // should be Vector(1, 1, 0)
    assert(add == Vector(1, 1, 0));

    Vector sub = unit_x - unit_y; // should be Vector(1, -1, 0)
    assert(sub == Vector(1, -1, 0));

    Vector neg = -unit_x; // should be Vector(-1, 0, 0)
    assert(neg == Vector(-1, 0, 0));

    Vector scal = 10.1 * unit_x; // should be Vector(10.1, 0, 0)
    assert(scal == Vector(10.1, 0, 0));

    std::cout << "Vector tests are okay!" << std::endl;
}

// Test function for Ray class
void test_ray()
{
    Vector v1 = Vector(1.2, 0.64, -101.875);
    Vector v2 = Vector(0, -45.8, 1.2);

    Ray r = Ray(v1, v2);

    // Test get_start and get_direction
    assert(r.get_start() == v1);     // should be v1
    assert(r.get_direction() == v2); // should be v2

    std::cout << "Ray tests are okay!" << std::endl;
}

// Test function for Color class
void test_color()
{
    Color col1 = Color();                // Should have only 0 values
    Color col2 = Color(1.1, 201.2, 9.1); // r=1.1, g=201.2, b=9.1

    // Test get_r, get_g, get_b
    assert(col2.get_red() == 1.1);
    assert(col2.get_green() == 201.2);
    assert(col2.get_blue() == 9.1);

    // Test color operations
    Color sum = col1 + col2; // r=1.1, g=201.2, b=9.1
    assert(sum == Color(1.1, 201.2, 9.1));

    sum += col2; // r = 2.2, g=402.4, b=18.2
    assert(sum == Color(2.2, 402.4, 18.2));

    Color scale = 10.1 * col2; // r=11.11, g=2,032.12, b=91.91
    assert(scale == Color(11.11, 2032.12, 91.91));

    std::cout << "Color tests are okay!" << std::endl;
}

int main()
{
    test_vector();
    test_ray();
    test_color();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

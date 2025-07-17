#include "scene.hpp"
#include "shapes.hpp"
#include "array.hpp"
#include <fstream>
#include <memory>
#include <vector>

void write_ppm(const Array2D<Color> &pixels, const std::string &filename)
{
  std::ofstream out(filename, std::ios::binary | std::ios::out);
  out.write("P6\n", 3);
  std::string s = std::to_string(pixels.get_width());
  out.write(s.c_str(), s.length());
  out.write(" ", 1);
  s = std::to_string(pixels.get_height());
  out.write(s.c_str(), s.length());
  out.write("\n255\n", 5);
  char color[3];
  for (unsigned y = 0; y < pixels.get_height(); y++)
  {
    for (unsigned x = 0; x < pixels.get_width(); x++)
    {
      Color c = pixels.get(x, y);
      color[0] = c.get_r();
      color[1] = c.get_g();
      color[2] = c.get_b();
      out.write(color, 3);
    }
  }
  out.close();
}

int main()
{
  int image_width = 512;
  int image_height = 512;

  Vector camera(0.5, -1.0, 0.5);
  Vector light(0.0, -0.5, 1.0);

  Scene scene(camera, light);

  scene.add_shape(std::make_shared<Plane>(Color(255, 255, 255), 0.0, Vector(0, 0, 0), Vector(0, 0, 1)));
  scene.add_shape(std::make_shared<Sphere>(Color(255, 0, 0), 0.3, Vector(0.25, 0.45, 0.4), 0.4));
  scene.add_shape(std::make_shared<Sphere>(Color(0, 255, 0), 0.0, Vector(1.0, 1.0, 0.25), 0.25));
  scene.add_shape(std::make_shared<Sphere>(Color(0, 0, 255), 0.7, Vector(0.8, 0.3, 0.15), 0.15));

  Array2D<Color> image(image_width, image_height);
  for (int y = 0; y < image_height; ++y)
  {
    for (int x = 0; x < image_width; ++x)
    {
      double px = static_cast<double>(x);
      double py = static_cast<double>(y);
      double screen_x = px / image_width;
      double screen_y = 0.0;
      double screen_z = (image_height - py) / image_width;

      Vector pixel_pos(screen_x, screen_y, screen_z);
      image.set(x, y, scene.compute_point_color(pixel_pos));
    }
  }

  write_ppm(image, "output.ppm");

  return 0;
}

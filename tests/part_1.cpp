#include <iostream>
#include "mesh.hpp"
#include "tests.hpp"

int main(int argc, char const *argv[])
{
  Mesh mesh_4elt("../input/square2d_4elt.msh");
  Mesh mesh_perforated("../input/square2d_perforated.msh");

  std::cout << "----------------------------" << std::endl;

  std::cout << "Area: " << mesh_4elt.area() << std::endl;
  std::cout << "Perimeter: " << mesh_4elt.perimeter() << std::endl;

  std::cout << "Test area 4elt passed: " << std::boolalpha << check_double_equal(mesh_4elt.area(), 1.0, 1e-4) << std::endl;
  std::cout << "Test perimeter 4elt passed: " << std::boolalpha << check_double_equal(mesh_4elt.perimeter(), 4.0, 1e-4) << std::endl;

  std::cout << "----------------------------" << std::endl;

  std::cout << "Area: " << mesh_perforated.area() << std::endl;
  std::cout << "Perimeter: " << mesh_perforated.perimeter() << std::endl;

  std::cout << "Test area perforated passed: " << std::boolalpha << check_double_equal(mesh_perforated.area(), 0.837725, 1e-4) << std::endl;
  std::cout << "Test perimeter perforated passed: " << std::boolalpha << check_double_equal(mesh_perforated.perimeter(), 11.5086, 1e-4) << std::endl;

  return 0;
}

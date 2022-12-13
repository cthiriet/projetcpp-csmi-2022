#include "physical_name.hpp"

PhysicalName::PhysicalName(int dimension, int id, std::string name)
{
  M_dimension = dimension;
  M_id = id;
  M_name = name;
}

PhysicalName::~PhysicalName() {}

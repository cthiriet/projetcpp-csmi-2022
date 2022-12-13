#include "tests.hpp"
#include <cmath>

bool check_double_equal(double a, double b, double tol)
{
  return std::abs(a - b) < tol;
}

bool check_double_not_equal(double a, double b, double tol)
{
  return std::abs(a - b) > tol;
}
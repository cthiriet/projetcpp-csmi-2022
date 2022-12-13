#include <iostream>
#include "mesh.hpp"
#include "evaluator_expr.hpp"
#include "export_vtk.hpp"
#include "tests.hpp"

int main(int argc, char const *argv[])
{
  /**
   * Load meshes
   */
  Mesh mesh_M0("../input/square2d_M0.msh");
  Mesh mesh_M1("../input/square2d_M1.msh");
  Mesh mesh_M2("../input/square2d_M2.msh");
  Mesh mesh_perforated("../input/square2d_perforated.msh");

  /**
   * Evaluate functions on meshes
   */
  EvaluatorExpr eval_f1([](double x, double y)
                        { return x * x + y * y; });

  EvaluatorExpr eval_f2([](double x, double y)
                        { return pow(x - 0.5, 2) + pow(y - 0.5, 2); });

  export_vtk(mesh_M2, eval_f1, "../mesh_M2_eval");
  export_vtk(mesh_perforated, eval_f2, "../mesh_perforated_eval");

  /**
   * Compute integrals and compare with exact values
   */
  EvaluatorExpr eval_fx1([](double x, double y)
                         { return pow(x, 1); });

  EvaluatorExpr eval_fx2([](double x, double y)
                         { return pow(x, 2); });

  EvaluatorExpr eval_fx3([](double x, double y)
                         { return pow(x, 3); });

  EvaluatorExpr eval_fx4([](double x, double y)
                         { return pow(x, 4); });

  EvaluatorExpr eval_fsin([](double x, double y)
                          { return sin(x); });

  double tol = 1e-12;

  std::cout << "----------------------------------------" << std::endl;

  double exact1 = 1. / 2.;
  std::cout << "test passed pow(x, 1) (ord 1): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact1 - mesh_M0.integral(1, eval_fx1), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 1) (ord 2): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact1 - mesh_M0.integral(2, eval_fx1), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 1) (ord 3): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact1 - mesh_M0.integral(3, eval_fx1), 0., tol) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  double exact2 = 1. / 3.;
  std::cout << "test passed pow(x, 2) (ord 1): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact2 - mesh_M0.integral(1, eval_fx2), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 2) (ord 2): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact2 - mesh_M0.integral(2, eval_fx2), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 2) (ord 3): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact2 - mesh_M0.integral(3, eval_fx2), 0., tol) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  double exact3 = 1. / 4.;
  std::cout << "test passed pow(x, 3) (ord 1): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact3 - mesh_M0.integral(1, eval_fx3), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 3) (ord 2): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact3 - mesh_M0.integral(2, eval_fx3), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 3) (ord 3): " << std::setprecision(15) << std::boolalpha << check_double_equal(exact3 - mesh_M0.integral(3, eval_fx3), 0., tol) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  double exact4 = 1. / 5.;
  std::cout << "test passed pow(x, 4) (ord 1): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact4 - mesh_M0.integral(1, eval_fx4), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 4) (ord 2): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact4 - mesh_M0.integral(2, eval_fx4), 0., tol) << std::endl;
  std::cout << "test passed pow(x, 4) (ord 3): " << std::setprecision(15) << std::boolalpha << check_double_not_equal(exact4 - mesh_M0.integral(3, eval_fx4), 0., tol) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  double exact5 = -cos(1.) + 1.;
  std::cout << "error integral sin(x) (ord 1 ; mesh_M0): " << std::setprecision(15) << exact5 - mesh_M0.integral(1, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 2 ; mesh_M0): " << std::setprecision(15) << exact5 - mesh_M0.integral(2, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 3 ; mesh_M0): " << std::setprecision(15) << exact5 - mesh_M0.integral(3, eval_fsin) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  std::cout << "error integral sin(x) (ord 1 ; mesh_M1): " << std::setprecision(15) << exact5 - mesh_M1.integral(1, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 2 ; mesh_M1): " << std::setprecision(15) << exact5 - mesh_M1.integral(2, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 3 ; mesh_M1): " << std::setprecision(15) << exact5 - mesh_M1.integral(3, eval_fsin) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  std::cout << "error integral sin(x) (ord 1 ; mesh_M2): " << std::setprecision(15) << exact5 - mesh_M2.integral(1, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 2 ; mesh_M2): " << std::setprecision(15) << exact5 - mesh_M2.integral(2, eval_fsin) << std::endl;
  std::cout << "error integral sin(x) (ord 3 ; mesh_M2): " << std::setprecision(15) << exact5 - mesh_M2.integral(3, eval_fsin) << std::endl;

  std::cout << "----------------------------------------" << std::endl;

  return 0;
}

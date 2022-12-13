#include <iostream>
#include "mesh.hpp"
#include "evaluator_expr.hpp"
#include "finite_element.hpp"
#include "export_vtk.hpp"

int main(int argc, char const *argv[])
{
  Mesh mesh_M2("../input/square2d_M2.msh");
  Mesh mesh_perforated("../input/square2d_perforated.msh");

  EvaluatorExpr eval_f([](double x, double y)
                       { return 1.; });

  EvaluatorExpr eval_g([](double x, double y)
                       { return 0.; });

  FiniteElement fe_M2(&mesh_M2);
  Eigen::VectorXd sol_M2 = fe_M2.solve(eval_f, eval_g, 3);
  export_vtk_vector(mesh_M2, sol_M2, "../square2d_M2_sol");

  FiniteElement fe_perf(&mesh_perforated);
  Eigen::VectorXd sol_perf = fe_perf.solve(eval_f, eval_g, 3);
  export_vtk_vector(mesh_perforated, sol_perf, "../square2d_perforated_sol");

  return 0;
}

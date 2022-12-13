#ifndef FINITE_ELEMENT_HPP
#define FINITE_ELEMENT_HPP

#include <set>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "mesh.hpp"
#include "element.hpp"
#include "evaluator.hpp"

class FiniteElement
{
private:
  Mesh *M_mesh;

public:
  FiniteElement(Mesh *mesh);

  Eigen::VectorXd solve(Evaluator const &eval_f, Evaluator const &eval_g, int quad_order = 3) const;

  ~FiniteElement();
};

#endif

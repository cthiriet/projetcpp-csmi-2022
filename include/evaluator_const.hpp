#ifndef EVALUATOR_CONST_HPP
#define EVALUATOR_CONST_HPP

#include "evaluator.hpp"

class EvaluatorConst : public Evaluator
{
public:
  EvaluatorConst(double c)
      : M_c(c)
  {
  }
  double operator()(double x, double y) const override { return M_c; }

private:
  double M_c;
};

#endif
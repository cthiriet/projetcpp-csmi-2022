#ifndef EVALUATOR_EXPR_HPP
#define EVALUATOR_EXPR_HPP

#include "evaluator.hpp"

class EvaluatorExpr : public Evaluator
{
public:
  EvaluatorExpr(double (*f)(double, double))
      : M_f(f)
  {
  }
  double operator()(double x, double y) const override { return M_f(x, y); }

private:
  double (*M_f)(double, double);
};

#endif
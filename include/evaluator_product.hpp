#ifndef EVALUATOR_PRODUCT_HPP
#define EVALUATOR_PRODUCT_HPP

#include "evaluator.hpp"

class EvaluatorProduct : public Evaluator
{
public:
  EvaluatorProduct(const Evaluator &e1, const Evaluator &e2)
      : M_e1(e1), M_e2(e2)
  {
  }
  double operator()(double x, double y) const override { return M_e1(x, y) * M_e2(x, y); }

private:
  const Evaluator &M_e1;
  const Evaluator &M_e2;
};

#endif
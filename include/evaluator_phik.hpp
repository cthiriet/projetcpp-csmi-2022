#ifndef EVALUATOR_PHIK_HPP
#define EVALUATOR_PHIK_HPP

#include "evaluator.hpp"
#include "node.hpp"
#include "element.hpp"

class EvaluatorPhiK : public Evaluator
{
private:
  Node **M_n;
  int M_k;
  const Element *M_e;

public:
  EvaluatorPhiK(Node **n, int k, const Element *e)
      : M_n(n), M_k(k), M_e(e)
  {
  }

  double operator()(double x, double y) const override { return this->getE()->phi_k(this->getN(), this->getK(), x, y); };

  const Element *getE() const { return M_e; }
  Node **getN() const { return M_n; }
  int getK() const { return M_k; }
};

#endif
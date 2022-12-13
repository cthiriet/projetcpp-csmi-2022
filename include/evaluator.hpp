#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

class Evaluator
{
public:
  virtual double operator()(double x, double y) const = 0;

private:
};

#endif
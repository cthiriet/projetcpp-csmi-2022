#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "element.hpp"
#include "evaluator.hpp"
#include "evaluator_product.hpp"
#include "evaluator_const.hpp"
#include "evaluator_phik.hpp"

Element::Element(int id, int type, int tag, int physical_name_id, int *node_ids)
{
  M_id = id;
  M_type = type; // 1: segment, 2: triangle
  M_physical_name_id = physical_name_id;
  M_node_ids = node_ids;
}

int Element::type() const { return M_type; }

int Element::node_id(int i) const { return M_node_ids[i]; }

double Element::area(Node **nodes) const
{
  if (M_type == 1)
    return 0.;

  double x1 = nodes[M_node_ids[0]]->x();
  double y1 = nodes[M_node_ids[0]]->y();
  double x2 = nodes[M_node_ids[1]]->x();
  double y2 = nodes[M_node_ids[1]]->y();
  double x3 = nodes[M_node_ids[2]]->x();
  double y3 = nodes[M_node_ids[2]]->y();

  return 0.5 * abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}

double Element::integral(int quad_order, Evaluator const &eval_f, Node **nodes) const
{
  double res = 0.;

  if (quad_order != 1 && quad_order != 2 && quad_order != 3)
  {
    std::cerr << "Error: wrong quadrature order." << std::endl;
    exit(1);
  }

  Node *n1 = nodes[this->node_id(0)];
  Node *n2 = nodes[this->node_id(1)];
  Node *n3 = nodes[this->node_id(2)];

  double x1 = n1->x();
  double y1 = n1->y();

  double x2 = n2->x();
  double y2 = n2->y();

  double x3 = n3->x();
  double y3 = n3->y();

  // area of the triangle
  double S = this->area(nodes);

  if (quad_order == 1)
  {
    double lambda_1 = 1. / 3.;
    double lambda_2 = 1. / 3.;
    double lambda_3 = 1. / 3.;

    double l_x = lambda_1 * x1 + lambda_2 * x2 + lambda_3 * x3;
    double l_y = lambda_1 * y1 + lambda_2 * y2 + lambda_3 * y3;

    double f = eval_f(l_x, l_y);

    res += S * f;
  }

  if (quad_order == 2)
  {
    double lambda_11 = 2. / 3.;
    double lambda_12 = 1. / 6.;
    double lambda_13 = 1. / 6.;

    double lambda_21 = 1. / 6.;
    double lambda_22 = 2. / 3.;
    double lambda_23 = 1. / 6.;

    double lambda_31 = 1. / 6.;
    double lambda_32 = 1. / 6.;
    double lambda_33 = 2. / 3.;

    double l_x1 = lambda_11 * x1 + lambda_12 * x2 + lambda_13 * x3;
    double l_y1 = lambda_11 * y1 + lambda_12 * y2 + lambda_13 * y3;

    double l_x2 = lambda_21 * x1 + lambda_22 * x2 + lambda_23 * x3;
    double l_y2 = lambda_21 * y1 + lambda_22 * y2 + lambda_23 * y3;

    double l_x3 = lambda_31 * x1 + lambda_32 * x2 + lambda_33 * x3;
    double l_y3 = lambda_31 * y1 + lambda_32 * y2 + lambda_33 * y3;

    double f1 = eval_f(l_x1, l_y1);
    double f2 = eval_f(l_x2, l_y2);
    double f3 = eval_f(l_x3, l_y3);

    double w = S / 3.;

    res += w * (f1 + f2 + f3);
  }

  if (quad_order == 3)
  {
    double lambda_11 = 1. / 3.;
    double lambda_12 = 1. / 3.;
    double lambda_13 = 1. / 3.;

    double lambda_21 = 3. / 5.;
    double lambda_22 = 1. / 5.;
    double lambda_23 = 1. / 5.;

    double lambda_31 = 1. / 5.;
    double lambda_32 = 3. / 5.;
    double lambda_33 = 1. / 5.;

    double lambda_41 = 1. / 5.;
    double lambda_42 = 1. / 5.;
    double lambda_43 = 3. / 5.;

    double l_x1 = lambda_11 * x1 + lambda_12 * x2 + lambda_13 * x3;
    double l_y1 = lambda_11 * y1 + lambda_12 * y2 + lambda_13 * y3;

    double l_x2 = lambda_21 * x1 + lambda_22 * x2 + lambda_23 * x3;
    double l_y2 = lambda_21 * y1 + lambda_22 * y2 + lambda_23 * y3;

    double l_x3 = lambda_31 * x1 + lambda_32 * x2 + lambda_33 * x3;
    double l_y3 = lambda_31 * y1 + lambda_32 * y2 + lambda_33 * y3;

    double l_x4 = lambda_41 * x1 + lambda_42 * x2 + lambda_43 * x3;
    double l_y4 = lambda_41 * y1 + lambda_42 * y2 + lambda_43 * y3;

    double f1 = eval_f(l_x1, l_y1);
    double f2 = eval_f(l_x2, l_y2);
    double f3 = eval_f(l_x3, l_y3);
    double f4 = eval_f(l_x4, l_y4);

    double w1 = -9. / 16. * S;
    double w2 = 25. / 48. * S;

    res += w1 * f1 + w2 * (f2 + f3 + f4);
  }

  return res;
}

double Element::phi_k(Node **nodes, int k, double x, double y) const
{
  double x1 = nodes[M_node_ids[0]]->x();
  double y1 = nodes[M_node_ids[0]]->y();
  double x2 = nodes[M_node_ids[1]]->x();
  double y2 = nodes[M_node_ids[1]]->y();
  double x3 = nodes[M_node_ids[2]]->x();
  double y3 = nodes[M_node_ids[2]]->y();

  double area = this->area(nodes);

  if (k == 1)
    return (x2 * y3 - x3 * y2 + x * (y2 - y3) + y * (x3 - x2)) / (2 * area);
  else if (k == 2)
    return (x3 * y1 - x1 * y3 + x * (y3 - y1) + y * (x1 - x3)) / (2 * area);
  else if (k == 3)
    return (x1 * y2 - x2 * y1 + x * (y1 - y2) + y * (x2 - x1)) / (2 * area);
  else
  {
    std::cerr << "Error: wrong index of basis function." << std::endl;
    exit(1);
  }
}

std::tuple<double, double> Element::grad_phi_k(Node **nodes, int k) const
{
  double x1 = nodes[M_node_ids[0]]->x();
  double y1 = nodes[M_node_ids[0]]->y();
  double x2 = nodes[M_node_ids[1]]->x();
  double y2 = nodes[M_node_ids[1]]->y();
  double x3 = nodes[M_node_ids[2]]->x();
  double y3 = nodes[M_node_ids[2]]->y();

  double area = this->area(nodes);

  if (k == 1)
    return std::make_tuple((y2 - y3) / (2 * area), (x3 - x2) / (2 * area));
  else if (k == 2)
    return std::make_tuple((y3 - y1) / (2 * area), (x1 - x3) / (2 * area));
  else if (k == 3)
    return std::make_tuple((y1 - y2) / (2 * area), (x2 - x1) / (2 * area));
  else
  {
    std::cerr << "Error: wrong index of basis function." << std::endl;
    exit(1);
  }
}

Eigen::MatrixXd Element::AKe(Node **nodes, int quad_order) const
{
  Eigen::MatrixXd AK(3, 3);
  AK.setZero();

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      std::tuple<double, double> grad_phi_i = this->grad_phi_k(nodes, i + 1);
      std::tuple<double, double> grad_phi_j = this->grad_phi_k(nodes, j + 1);

      double res = std::get<0>(grad_phi_i) * std::get<0>(grad_phi_j) + std::get<1>(grad_phi_i) * std::get<1>(grad_phi_j);

      EvaluatorConst eval(res);

      AK(i, j) = this->integral(quad_order, eval, nodes);
    }
  }

  return AK;
}

Eigen::VectorXd Element::FKe(Node **nodes, Evaluator const &eval_f, int quad_order) const
{
  Eigen::VectorXd FK(3);
  FK.setZero();

  for (int i = 0; i < 3; i++)
  {
    EvaluatorPhiK eval_phi_k(nodes, i + 1, this);
    EvaluatorProduct eval_g(eval_f, eval_phi_k);
    FK(i) = this->integral(quad_order, eval_g, nodes);
  }

  return FK;
}

Element::~Element()
{
}
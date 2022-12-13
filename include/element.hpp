#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "evaluator.hpp"
#include "node.hpp"

class Element
{
private:
  int M_id;
  int M_type;
  int M_tag = 2;
  int M_physical_name_id = 1;
  int *M_node_ids;

public:
  Element(int id = 0, int type = 1, int tag = 2, int physical_name_id = 0, int *node_ids = nullptr);

  int type() const;
  int node_id(int i) const;
  double area(Node **nodes) const;
  double integral(int quad_order, Evaluator const &eval_f, Node **nodes) const;
  double phi_k(Node **nodes, int k, double x, double y) const;
  std::tuple<double, double> grad_phi_k(Node **nodes, int k) const;
  Eigen::MatrixXd AKe(Node **nodes, int quad_order = 3) const;
  Eigen::VectorXd FKe(Node **nodes, Evaluator const &eval_f, int quad_order = 3) const;

  friend std::ostream &operator<<(std::ostream &os, const Element &e)
  {
    for (int i = 0; i < e.M_type + 1; i++)
    {
      os << " " << e.M_node_ids[i];
    }
    return os;
  }

  friend std::istream &operator>>(std::istream &is, Element &el)
  {
    int id, type, tag, physical_name_id, tag_geom;
    int *node_ids = new int[type + 1];

    is >> id >> type >> tag >> physical_name_id >> tag_geom;
    for (int i = 0; i < type + 1; i++)
      is >> node_ids[i];

    for (int i = 0; i < type + 1; i++)
      node_ids[i] -= 1;

    el.M_id = id - 1;
    el.M_type = type;
    el.M_tag = tag;
    el.M_physical_name_id = physical_name_id;
    el.M_node_ids = node_ids;

    return is;
  }

  ~Element();
};

#endif
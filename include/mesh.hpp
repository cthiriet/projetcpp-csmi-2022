#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "physical_name.hpp"
#include "node.hpp"
#include "element.hpp"

class Mesh
{
private:
  int M_nb_physical_names; // number of physical names
  int M_nb_nodes;          // number of nodes (Np)
  int M_nb_elements;       // number of elements (Ne)
  PhysicalName **M_physical_names;
  Node **M_nodes;
  Element **M_elements;

  int M_nb_edges;        // number of edges (Ib)
  std::set<int> M_edges; // a set containing the node_id of the edges

public:
  Mesh();
  Mesh(std::string filename);

  int nb_physical_names() const;
  PhysicalName *physical_name(int i) const;

  int nb_nodes() const;
  Node **nodes() const;
  Node *node(int i) const;

  int nb_elements() const;
  Element *element(int i) const;

  int nb_triangles() const;
  Element *triangle(int i) const;

  int nb_edges() const;
  int edge(int i) const;

  int global_dof(Element *triangle, int k) const;

  double area() const;
  double perimeter() const;
  double integral(int quad_order, Evaluator const &eval_f) const;

  ~Mesh();
};

#endif
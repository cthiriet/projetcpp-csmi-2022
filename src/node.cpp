#include "node.hpp"

Node::Node(int id, double x, double y, double z)
{
  M_id = id;
  M_x = x;
  M_y = y;
  M_z = z;
}

int Node::id() const { return M_id; }

double Node::x() const { return M_x; }

double Node::y() const { return M_y; }

double Node::z() const { return M_z; }

Node::~Node() {}

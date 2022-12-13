#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class Node
{
private:
  int M_id;
  double M_x;
  double M_y;
  double M_z;

public:
  Node(int id = 0, double x = 0., double y = 0., double z = 0.);

  int id() const;
  double x() const;
  double y() const;
  double z() const;

  friend std::ostream &operator<<(std::ostream &os, const Node &n)
  {
    os << n.M_x << " " << n.M_y << " " << n.M_z;
    return os;
  }

  friend std::istream &operator>>(std::istream &is, Node &node)
  {
    int id;
    double x, y, z;
    is >> id >> x >> y >> z;

    node.M_id = id - 1;
    node.M_x = x;
    node.M_y = y;
    node.M_z = z;

    return is;
  }

  ~Node();
};

#endif
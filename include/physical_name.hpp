#ifndef PHYSICAL_NAME_HPP
#define PHYSICAL_NAME_HPP

#include <string>
#include <iostream>

class PhysicalName
{
private:
  int M_dimension;
  int M_id;
  std::string M_name;

public:
  PhysicalName(int dimension = 0, int id = 0, std::string name = "none");

  friend std::ostream &operator<<(std::ostream &os, const PhysicalName &pn)
  {
    os << pn.M_dimension << " " << pn.M_id << " " << pn.M_name;
    return os;
  }

  friend std::istream &operator>>(std::istream &is, PhysicalName &phy)
  {
    int dim, id;
    std::string s;
    is >> dim >> id >> s;

    phy.M_dimension = dim;
    phy.M_id = id;
    phy.M_name = s;

    return is;
  }

  ~PhysicalName();
};

#endif
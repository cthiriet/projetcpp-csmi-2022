#include "mesh.hpp"

Mesh::Mesh()
{
  M_nb_physical_names = 0;
  M_nb_nodes = 0;
  M_nb_elements = 0;
  M_physical_names = nullptr;
  M_nodes = nullptr;
  M_elements = nullptr;
  M_nb_edges = 0;
}

Mesh::Mesh(std::string filename)
{
  std::cout << "Loading mesh from file " << filename << std::endl;

  int part = 1;

  std::ifstream ifile(filename);

  if (ifile.is_open())
  {
    bool nb_physical_names_done = false;
    int i_physical_name = 0;

    bool nb_nodes_done = false;
    int i_node = 0;

    bool nb_elements_done = false;
    int i_element = 0;

    while (!ifile.eof())
    {
      std::string line;
      std::getline(ifile, line);
      std::istringstream iss(line);

      if (line == "$EndMeshFormat")
      {
        part = 2;
        continue;
      }

      if (line == "$EndPhysicalNames")
      {
        part = 3;
        continue;
      }

      if (line == "$EndNodes")
      {
        part = 4;
        continue;
      }

      if (line == "$EndElements")
        break;

      // check if line contains '$'
      if (line.find("$") != std::string::npos)
        continue;

      // check version of the file
      if (part == 1)
      {
        double version, d2, d3;
        iss >> version >> d2 >> d3;

        if (version != 2.2)
        {
          std::cerr << "Error: wrong version of the file." << std::endl;
          exit(1);
        }
      }

      // parse physical names
      if (part == 2)
      {
        if (!nb_physical_names_done)
        {
          iss >> M_nb_physical_names;
          // cout << "Number of physical names: " << M_nb_physical_names << endl;
          M_physical_names = new PhysicalName *[M_nb_physical_names];
          nb_physical_names_done = true;
        }
        else
        {
          M_physical_names[i_physical_name] = new PhysicalName;
          iss >> *M_physical_names[i_physical_name];
          ++i_physical_name;
        }
      }

      // parse nodes
      if (part == 3)
      {
        if (!nb_nodes_done)
        {
          iss >> M_nb_nodes;
          // cout << "Number of nodes: " << M_nb_nodes << endl;
          M_nodes = new Node *[M_nb_nodes];
          nb_nodes_done = true;
        }
        else
        {
          M_nodes[i_node] = new Node;
          iss >> *M_nodes[i_node];
          ++i_node;
        }
      }

      // parse elements
      if (part == 4)
      {
        if (!nb_elements_done)
        {
          iss >> M_nb_elements;
          // cout << "Number of elements: " << M_nb_elements << endl;
          M_elements = new Element *[M_nb_elements];
          nb_elements_done = true;
        }
        else
        {
          M_elements[i_element] = new Element;
          iss >> *M_elements[i_element];
          ++i_element;
        }
      }
    }
  }
  else
  {
    std::cout << "Error when opening the file " << filename << std::endl;
    exit(1);
  }

  // -----------------------------------------------------------------------//
  // compute Ib
  // -----------------------------------------------------------------------//
  for (int i = 0; i < M_nb_elements; i++)
  {
    if (M_elements[i]->type() == 1)
    {
      M_edges.insert(M_elements[i]->node_id(0));
      M_edges.insert(M_elements[i]->node_id(1));
    }
  }

  // cout << "Ib: " << M_edges.size() << endl;
  M_nb_edges = M_edges.size();
}

int Mesh::nb_physical_names() const { return M_nb_physical_names; }

int Mesh::nb_nodes() const { return M_nb_nodes; }

int Mesh::nb_elements() const { return M_nb_elements; }

int Mesh::nb_triangles() const
{
  int nb_triangles = 0;
  for (int i = 0; i < M_nb_elements; i++)
  {
    if (M_elements[i]->type() == 2)
      ++nb_triangles;
  }
  return nb_triangles;
}

int Mesh::nb_edges() const
{
  return M_nb_edges;
}

Node **Mesh::nodes() const { return M_nodes; }

int Mesh::edge(int i) const
{
  auto it = M_edges.begin();
  advance(it, i);
  return *it;
}

Element *Mesh::triangle(int i) const
{
  int nb_triangles = 0;
  for (int j = 0; j < M_nb_elements; j++)
  {
    if (M_elements[j]->type() == 2)
    {
      if (nb_triangles == i)
        return M_elements[j];
      ++nb_triangles;
    }
  }
  std::cerr << "Error: triangle " << i << " does not exist." << std::endl;
  exit(1);
}

int Mesh::global_dof(Element *triangle, int k) const
{
  return triangle->node_id(k);
}

PhysicalName *Mesh::physical_name(int i) const { return M_physical_names[i]; }

Node *Mesh::node(int i) const { return M_nodes[i]; }

Element *Mesh::element(int i) const { return M_elements[i]; }

double Mesh::area() const
{
  double area = 0.0;
  for (int i = 0; i < M_nb_elements; i++)
  {
    Element *e = M_elements[i];
    if (e->type() == 2)
      area += e->area(M_nodes);
  }
  return area;
}

double Mesh::perimeter() const
{
  double perimeter = 0.;
  for (int i = 0; i < M_nb_elements; i++)
  {
    Element *e = M_elements[i];
    if (e->type() == 1)
    {
      Node *n1 = M_nodes[e->node_id(0)];
      Node *n2 = M_nodes[e->node_id(1)];
      perimeter += sqrt(pow(n2->x() - n1->x(), 2) + pow(n2->y() - n1->y(), 2));
    }
  }
  return perimeter;
}

double Mesh::integral(int quad_order, Evaluator const &eval_f) const
{
  double res = 0.;

  if (quad_order != 1 && quad_order != 2 && quad_order != 3)
  {
    std::cerr << "Error: wrong quadrature order." << std::endl;
    exit(1);
  }

  for (int i = 0; i < this->nb_triangles(); i++)
  {
    Element *e = this->triangle(i);
    res += e->integral(quad_order, eval_f, M_nodes);
  }

  return res;
}

Mesh::~Mesh() {}
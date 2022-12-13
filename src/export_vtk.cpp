#include "export_vtk.hpp"

void export_vtk(Mesh &mesh, Evaluator const &eval_f, std::string file_name)
{
  std::ofstream ofile(file_name + ".vtk");

  ofile << "# vtk DataFile Version 2.0" << std::endl;
  ofile << "my example" << std::endl;
  ofile << "ASCII" << std::endl;
  ofile << "DATASET UNSTRUCTURED_GRID" << std::endl;

  ofile << "POINTS " << mesh.nb_nodes() << " float" << std::endl;
  for (int i = 0; i < mesh.nb_nodes(); i++)
    ofile << *mesh.node(i) << std::endl;

  int nb_triangles = mesh.nb_triangles();
  ofile << "CELLS " << nb_triangles << " " << 4 * nb_triangles << std::endl;
  for (int i = 0; i < nb_triangles; i++)
    ofile << "3" << *mesh.triangle(i) << std::endl;

  ofile << "CELL_TYPES " << nb_triangles << std::endl;
  for (int i = 0; i < nb_triangles; i++)
    ofile << "5" << std::endl;

  ofile << "POINT_DATA " << mesh.nb_nodes() << std::endl;
  ofile << "SCALARS " << file_name << " float 1" << std::endl;
  ofile << "LOOKUP_TABLE default" << std::endl;

  for (int i = 0; i < mesh.nb_nodes(); i++)
  {
    Node *n = mesh.node(i);
    ofile << eval_f(n->x(), n->y()) << std::endl;
  }
}

void export_vtk_vector(Mesh &mesh, Eigen::VectorXd sol, std::string file_name)
{
  std::ofstream ofile(file_name + ".vtk");

  ofile << "# vtk DataFile Version 2.0" << std::endl;
  ofile << "my example" << std::endl;
  ofile << "ASCII" << std::endl;
  ofile << "DATASET UNSTRUCTURED_GRID" << std::endl;

  ofile << "POINTS " << mesh.nb_nodes() << " float" << std::endl;
  for (int i = 0; i < mesh.nb_nodes(); i++)
    ofile << *mesh.node(i) << std::endl;

  int nb_triangles = mesh.nb_triangles();
  ofile << "CELLS " << nb_triangles << " " << 4 * nb_triangles << std::endl;
  for (int i = 0; i < nb_triangles; i++)
    ofile << "3" << *mesh.triangle(i) << std::endl;

  ofile << "CELL_TYPES " << nb_triangles << std::endl;
  for (int i = 0; i < nb_triangles; i++)
    ofile << "5" << std::endl;

  ofile << "POINT_DATA " << mesh.nb_nodes() << std::endl;
  ofile << "SCALARS " << file_name << " float 1" << std::endl;
  ofile << "LOOKUP_TABLE default" << std::endl;

  for (int i = 0; i < mesh.nb_nodes(); i++)
    ofile << sol(i) << std::endl;
}

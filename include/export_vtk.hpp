#ifndef EXPORT_VTK_HPP
#define EXPORT_VTK_HPP

#include "mesh.hpp"
#include "evaluator.hpp"

void export_vtk(Mesh &mesh, Evaluator const &eval_f, std::string file_name);
void export_vtk_vector(Mesh &mesh, Eigen::VectorXd sol, std::string file_name);

#endif
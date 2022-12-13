#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include "evaluator_expr.hpp"
#include "mesh.hpp"
#include "finite_element.hpp"
#include "export_vtk.hpp"

int main(int argc, char const *argv[])
{
  // read file config.txt
  // get command line arguments for the path to the config file
  std::string config_file_path;
  if (argc > 1)
    config_file_path = argv[1];
  else
  {
    std::cerr << "Error: no config file path was provided." << std::endl;
    std::cerr << "./run <path-to-config-file>" << std::endl;
    exit(1);
  }

  // default parameters
  int quad_order = 1;
  std::string input_file_path;
  std::string output_file_path;

  std::ifstream ifile(config_file_path);
  if (!ifile.is_open())
  {
    std::cerr << "Error: cannot open file " << config_file_path << std::endl;
    exit(1);
  }

  while (!ifile.eof())
  {
    // get the line and separate the key and the value (the separator is "=")
    std::string line;
    std::getline(ifile, line);
    if (line.empty())
      continue;
    size_t pos = line.find("=");
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    // cout << key << "=" << value << endl;
    if (key == "quad_order")
      quad_order = std::stoi(value);
    else if (key == "input_file_path")
      input_file_path = value;
    else if (key == "output_file_path")
      output_file_path = value;
  }

  Mesh mesh(input_file_path);

  EvaluatorExpr eval_f([](double x, double y)
                       { return 1.; });

  EvaluatorExpr eval_g([](double x, double y)
                       { return 0.; });

  FiniteElement fe(&mesh);
  Eigen::VectorXd sol = fe.solve(eval_f, eval_g, quad_order);

  export_vtk_vector(mesh, sol, output_file_path);

  return 0;
}

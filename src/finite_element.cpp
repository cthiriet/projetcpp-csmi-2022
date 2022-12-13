#include "finite_element.hpp"

FiniteElement::FiniteElement(Mesh *mesh) : M_mesh(mesh) {}

Eigen::VectorXd FiniteElement::solve(Evaluator const &eval_f, Evaluator const &eval_g, int quad_order) const
{
  typedef Eigen::SparseMatrix<double, Eigen::RowMajor> sparse_matrix_type;
  sparse_matrix_type A(M_mesh->nb_nodes(), M_mesh->nb_nodes());
  Eigen::VectorXd F(M_mesh->nb_nodes());
  std::vector<Eigen::Triplet<double>> tripletList;

  for (int i = 0; i < M_mesh->nb_nodes(); ++i)
    F(i) = 0.;

  // -----------------------------------------------------------------------//
  // build matrix A
  // -----------------------------------------------------------------------//
  for (int e = 0; e < M_mesh->nb_elements(); e++)
  {
    Element *Ke = M_mesh->element(e);

    if (Ke->type() == 2)
    {
      Eigen::MatrixXd AKe = Ke->AKe(M_mesh->nodes(), quad_order);
      Eigen::VectorXd FKe = Ke->FKe(M_mesh->nodes(), eval_f, quad_order);

      for (int s = 0; s < 3; s++)
      {
        int i = M_mesh->global_dof(Ke, s);
        for (int t = 0; t < 3; t++)
        {
          int j = M_mesh->global_dof(Ke, t);

          double aij = A.coeffRef(i, j);

          tripletList.push_back(Eigen::Triplet<double>(i, j, aij + AKe(s, t)));
        }
        F(i) += FKe(s);
      }
    }
  }
  A.setFromTriplets(tripletList.begin(), tripletList.end());

  // -----------------------------------------------------------------------//
  // elimination
  // -----------------------------------------------------------------------//
  std::set<int> rows;

  for (int i = 0; i < M_mesh->nb_edges(); i++)
  {
    int edge = M_mesh->edge(i);
    rows.insert(edge);

    double xi = M_mesh->node(edge)->x();
    double yi = M_mesh->node(edge)->y();
    F(i) = eval_g(xi, yi);
  }

  for (int rowId : rows)
  {
    for (typename sparse_matrix_type::InnerIterator it(A, rowId); it; ++it)
    {
      if (it.row() == it.col())
      {
        it.valueRef() = 1.0;
      }
      else
      {
        it.valueRef() = 0;
      }
    }
  }

  // -----------------------------------------------------------------------//
  // solve linear system
  // -----------------------------------------------------------------------//
  Eigen::SparseLU<sparse_matrix_type> solver;
  solver.analyzePattern(A);
  solver.factorize(A);
  Eigen::VectorXd sol = solver.solve(F);

  return sol;
}

FiniteElement::~FiniteElement() {}

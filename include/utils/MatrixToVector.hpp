#ifndef _MATRIX_TO_VECTOR_HPP
#define _MATRIX_TO_VECTOR_HPP

#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace utils {
  class MatrixToVector {
  public:
    MatrixToVector(Matrix* a);

    vector<double> execute();
  private:
    Matrix* a;
  };
}

#endif


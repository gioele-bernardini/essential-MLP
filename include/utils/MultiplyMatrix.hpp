#ifndef _MULTIPLY_MATRIX_HPP
#define _MULTIPLY_MATRIX_HPP

#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace utils {
  class MultiplyMatrix {
  public:
    MultiplyMatrix(Matrix* a, Matrix* b);

    Matrix* execute();
  private:
    Matrix* a;
    Matrix* b;
    Matrix* c;
  };
}

#endif


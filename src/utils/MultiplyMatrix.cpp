#include "../../include/utils/MultiplyMatrix.hpp"

utils::MultiplyMatrix::MultiplyMatrix(Matrix* a, Matrix* b) {
  this->a = a;
  this->b = b;

  if (a->getNumCols() != b->getNumRows()) {
    cerr << "A_rows: " << a->getNumCols() << " != B_cols: " << b->getNumRows() << endl;

    assert(false);
  }

  this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

// "ijk" algorithm:
// i loops through A rows; j loops through B columns,
// k through A columns in i-row and B rows in j-column
Matrix* utils::MultiplyMatrix::execute() {
  for (int i = 0; i < a->getNumRows(); i++) {
    for (int j = 0; j < b->getNumCols(); j++) {
      for (int k = 0; k < b->getNumRows(); k++) {
        double p = this->a->getValue(i, k) * this->b->getValue(k, j);
        double newVal = this->c->getValue(i, j) + p;

        this->c->setValue(i, j, newVal);
      }
    }
  }

  return this->c;
}


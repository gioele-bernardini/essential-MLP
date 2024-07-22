#include "../include/Matrix.hpp"
#include <iostream>
#include <cassert>

void testMatrixCreation() {
  // Test matrix creation with zeros
  Matrix m1(3, 3, false);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      assert(m1.getValue(i, j) == 0.0);
    }
  }

  // Test matrix creation with random values
  Matrix m2(3, 3, true);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double val = m2.getValue(i, j);
      assert(val >= 0.0 && val <= 1.0);
    }
  }

  std::cout << "Matrix creation test passed.\n";
}

void testMatrixSetValue() {
  Matrix m(2, 2, false);
  m.setValue(0, 0, 5.5);
  m.setValue(1, 1, 3.3);
  assert(m.getValue(0, 0) == 5.5);
  assert(m.getValue(1, 1) == 3.3);

  std::cout << "Matrix set and get value test passed.\n";
}

void testMatrixTranspose() {
  Matrix m(2, 3, false);
  m.setValue(0, 0, 1.0);
  m.setValue(0, 1, 2.0);
  m.setValue(0, 2, 3.0);
  m.setValue(1, 0, 4.0);
  m.setValue(1, 1, 5.0);
  m.setValue(1, 2, 6.0);

  Matrix* t = m.transpose();
  assert(t->getValue(0, 0) == 1.0);
  assert(t->getValue(1, 0) == 2.0);
  assert(t->getValue(2, 0) == 3.0);
  assert(t->getValue(0, 1) == 4.0);
  assert(t->getValue(1, 1) == 5.0);
  assert(t->getValue(2, 1) == 6.0);

  std::cout << "Matrix transpose test passed.\n";

  delete t; // clean up dynamically allocated transpose matrix
}

int main() {
  testMatrixCreation();
  testMatrixSetValue();
  testMatrixTranspose();

  std::cout << "All tests passed.\n";
  return 0;
}


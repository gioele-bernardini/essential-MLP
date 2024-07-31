#include "../include/Matrix.hpp"
#include <iostream>
#include <cassert>

void testMatrixCreation() {
  // Test matrix creation with zeros
  Matrix m1(3, 3, false);
  std::cout << "Testing matrix creation with zeros:" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << "m1(" << i << ", " << j << ") = " << m1.getValue(i, j) << std::endl;
      assert(m1.getValue(i, j) == 0.0);
    }
  }

  // Test matrix creation with random values
  Matrix m2(3, 3, true);
  std::cout << "Testing matrix creation with random values:" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double val = m2.getValue(i, j);
      std::cout << "m2(" << i << ", " << j << ") = " << val << std::endl;
      assert(val >= 0.0 && val <= 1.0);
    }
  }

  std::cout << "Matrix creation test passed.\n";
}

void testMatrixSetValue() {
  Matrix m(2, 2, false);
  m.setValue(0, 0, 5.5);
  m.setValue(1, 1, 3.3);
  std::cout << "Testing matrix setValue:" << std::endl;
  std::cout << "m(0, 0) = " << m.getValue(0, 0) << std::endl;
  assert(m.getValue(0, 0) == 5.5);
  std::cout << "m(1, 1) = " << m.getValue(1, 1) << std::endl;
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

  std::cout << "Original matrix:" << std::endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << m.getValue(i, j) << "\t";
    }
    std::cout << std::endl;
  }

  Matrix* t = m.transpose();
  std::cout << "Transposed matrix:" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      std::cout << t->getValue(i, j) << "\t";
      assert(t->getValue(i, j) == m.getValue(j, i));
    }
    std::cout << std::endl;
  }

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


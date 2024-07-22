#include "../include/Matrix.hpp"
#include <random>

Matrix::Matrix(int numRows, int numCols, bool isRandom) {
  this->numRows = numRows;
  this->numCols = numCols;

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      
    }
  }
}

double Matrix::generateRandomNumber() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  return dis(gen);
}
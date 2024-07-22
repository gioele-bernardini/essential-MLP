#include "../include/Matrix.hpp"
#include <random>

Matrix::Matrix(int numRows, int numCols, bool isRandom) {
  this->numRows = numRows;
  this->numCols = numCols;

  for (int i = 0; i < numRows; i++) {
    vector <double> colValues;

    for (int j = 0; j < numCols; j++) {
      double r = 0.00;
      if (isRandom) {
        double r = this->generateRandomNumber();
      }

      colValues.push_back(r);
    }

    this->values.push_back(colValues);
  }
}

double Matrix::generateRandomNumber() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  return dis(gen);
}

void Matrix::setValue(int r, int c, double v) {
  this->values.at(r).at(c) = v;
}

double Matrix::getValue(int r, int c) {
  return this->values.at(r).at(c);
}

Matrix* Matrix::transpose() {
  // isRandom false for the new Matrix, just setting up zero's for now
  Matrix* m = new Matrix(this->numCols, this->numRows, false);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      m->setValue(i, j, this->getValue(j, i));
    }
  }
}

void Matrix::printToConsole() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      cout << this->values.at(i).at(j) << "\t\t";
    }

    cout << endl;
  }
}


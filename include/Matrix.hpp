#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix(int numRows, int numCols, bool isRandom);

  Matrix* transpose();

  double generateRandomNumber();

  void setValue(int r, int c, double v);
  double getValue(int r, int c);

  int getNumRows() { return this->numRows; }
  int getNumCols() { return this->numCols; }

  void printToConsole();
private:
  int numRows;
  int numCols;
  vector< vector<double> > values;
};

#endif


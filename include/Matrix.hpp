#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix(int numRows, int numCols, bool isRandom);

  Matrix* transpose();

  void setValue(int r, int c, double v);
  double getValue(int r, int c);
private:
  int numRows;
  int numCols;
  vector< vector<double> > values;
};

#endif


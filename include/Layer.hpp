#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include "Neuron.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Layer {
public:

  Layer(int size);

  void setVal(int i, double v);

  double getVal(int i);

  Matrix* toMatrixVals();
  Matrix* toMatrixActivatedVals();
  Matrix* toMatrixDerivedVals();
private:

  int size;
  vector<Neuron *> neurons;
};

#endif


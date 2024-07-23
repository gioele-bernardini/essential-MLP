#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include "Layer.hpp"
#include "Matrix.hpp"
#include <iostream>

using namespace std;

class NeuralNetwork {
public:
  NeuralNetwork(vector<int> topology);

  void setCurrentInput(vector<double> input);
private:
  int topologySize;

  vector<int> topology;
  vector<Layer *> layers;
  vector<Matrix *> weightMatrices;

  vector<double> input;
};

#endif


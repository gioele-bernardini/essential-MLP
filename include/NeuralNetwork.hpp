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

  // Getter methods mainly for testing
  int getTopologySize() const { return topologySize; }
  const vector<int>& getTopology() const { return topology; }
  const vector<Layer*>& getLayers() const { return layers; }
  const vector<Matrix*>& getWeightMatrices() const { return weightMatrices; }

private:
  // The number of layers
  int topologySize;

  // The vector for the size of the layers
  vector<int> topology;
  vector<Layer *> layers;
  
  // Contains the weight between one layer and the next one
  vector<Matrix *> weightMatrices;

  vector<double> input;
};

#endif


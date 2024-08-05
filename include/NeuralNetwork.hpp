#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include "Layer.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

class NeuralNetwork {
public:
  NeuralNetwork(vector<int> topology);

  void setCurrentInput(vector<double> input);
  void setCurrentTarget(vector<double> target) {
    this->target = target;
  }

  void feedForward();
  void backPropagation();
  void setErrors();

  // Getter methods mainly for testing
  int getTopologySize() const { return topologySize; }
  const vector<int>& getTopology() const { return topology; }
  const vector<Layer*>& getLayers() const { return layers; }
  const vector<Matrix*>& getWeightMatrices() const { return weightMatrices; }

  // Setter methods
  void setNeuronValue(int indexLayer, int indexNeuron, double val) {
    this->layers.at(indexLayer)->setVal(indexNeuron, val);
  }

  // Getter for the neurons matrices
  Matrix* getNeuronMatrix(int i);
  Matrix* getActivatedNeuronMatrix(int i);
  Matrix* getDerivedNeuronMatrix(int i);

  Matrix* getWeightMatrix(int i);

  void printInputToConsole();
  void printOutputToConsole();
  void printTargetToConsole();
  
  void printWeightMatrix(int i);
  void printHistoricalErrors();

  double getTotalError() { return this->error; }
  vector<double> getErrors() { return this->errors; }

private:
  // The number of layers
  int topologySize;

  // The vector for the size of the layers
  vector<int> topology;
  vector<Layer *> layers;
  
  // Contains the weight between one layer and the next one
  vector<Matrix *> weightMatrices;
  // Contains the gradients needed for the back propagation
  vector<Matrix*> gradientMatrices;

  vector<double> input;

  // For the Error
  vector<double> target;
  double error;
  vector<double> errors;
  vector<double> historicalErrors;
};

#endif


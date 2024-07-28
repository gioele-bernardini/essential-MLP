#include "NeuralNetwork.hpp"
#include "utils/MultiplyMatrix.hpp"
#include <vector>

NeuralNetwork::NeuralNetwork(vector<int> topology) {
  this->topology = topology;
  this->topologySize = topology.size();
  
  for (int i = 0; i < topologySize; i++) {
    Layer* l = new Layer(topology.at(i));
    this->layers.push_back(l);
  }

  // (topologySize -1) as the last Layer needs no such matrix
  for (int i = 0; i < (topologySize -1); i++) {
    Matrix* m = new Matrix(topology.at(i), topology.at(i +1), true);

    this->weightMatrices.push_back(m);
  }
}

void NeuralNetwork::setCurrentInput(vector<double> input) {
  this->input = input;

  for (int i = 0; i < input.size(); i++) {
    // Set the values in the layer [0] (input layer)
    this->layers.at(0)->setVal(i, input.at(i));
  }
}

void NeuralNetwork::printToConsole() {
  for (int i = 0; i < this->layers.size(); i++) {
    cout << "LAYER: " << i << endl;

    // First layer (input)
    if (i == 0) {
      Matrix* m = this->layers.at(i)->toMatrixVals();
      m->printToConsole();
      delete m;
    } else {
      Matrix* m = this->layers.at(i)->toMatrixActivatedVals();
      m->printToConsole();
      delete m;
    }
  }
}

void NeuralNetwork::printWeightMatrix(int i) {
  this->weightMatrices.at(i)->printToConsole();
}

// Feed Forward algorithm
void NeuralNetwork::feedForward() {
  for (int i = 0; i < (this->layers.size() - 1); i++) {
    // Get the neuron matrix for the current layer
    Matrix* a = this->getNeuronMatrix(i);

    // If not the input layer, get the activated neuron matrix
    if (i != 0) {
      delete a; // Delete the previous matrix to prevent memory leak
      a = this->getActivatedNeuronMatrix(i);
    }

    // Get the weight matrix for the current layer
    Matrix* b = this->getWeightMatrix(i);

    // Multiply the matrices a and b
    utils::MultiplyMatrix multiplyMatrix(a, b);
    Matrix* c = multiplyMatrix.execute();

    // Set the values in the next layer's neurons
    for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
      this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index));
    }

    // Clean up memory
    delete a;
    delete c;
  }
}


Matrix* NeuralNetwork::getNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixVals();
}

Matrix* NeuralNetwork::getActivatedNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixActivatedVals();
}

Matrix* NeuralNetwork::getDerivedNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixDerivedVals();
}

Matrix* NeuralNetwork::getWeightMatrix(int i) {
  return this->weightMatrices.at(i);
}


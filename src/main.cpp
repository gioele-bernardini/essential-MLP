#include "NeuralNetwork.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  vector<double> input;
  input.push_back(1);
  input.push_back(0);
  input.push_back(1);

  vector<int> topology;
  topology.push_back(3);
  topology.push_back(2);
  topology.push_back(1);

  NeuralNetwork* nn = new NeuralNetwork(topology);
  nn->setCurrentInput(input);

  nn->feedForward();

  nn->printWeightMatrix(0);

  return 0;
}


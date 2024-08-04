#include "NeuralNetwork.hpp"
#include <iostream>
#include <vector>

using namespace std;

#define N_EPOCH 5

int main(int argc, char** argv) {
  vector<double> input;
  input.push_back(1);
  input.push_back(0);
  input.push_back(1);

  vector<int> topology;
  topology.push_back(3);
  topology.push_back(2);
  topology.push_back(3);

  NeuralNetwork* nn = new NeuralNetwork(topology);
  nn->setCurrentInput(input);
  nn->setCurrentTarget(input);

  // Training Process
  for (int i = 0; i < N_EPOCH; i++) {
    nn->feedForward();
    nn->setErrors();
    nn->backPropagation();

    cout << "Total Error" << nn->getTotalError() << endl;
  }

  return 0;
}


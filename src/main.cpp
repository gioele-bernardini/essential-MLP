#include "NeuralNetwork.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Too high will result in over-fitting
#define N_EPOCHS 100

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
  for (int i = 0; i < N_EPOCHS; i++) {
    cout << "Epoch: " << i << endl;
    nn->feedForward();
    nn->setErrors();
    cout << "Total Error: " << nn->getTotalError() << endl;
    nn->backPropagation();

    cout << "====================" << endl;
    cout << "OUTPUT: "; 
    nn->printOutputToConsole();

    cout << "TARGET: ";
    nn->printInputToConsole();
    cout << "====================" << endl;

    cout << endl;
  }

  return 0;
}


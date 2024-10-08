#include "../include/NeuralNetwork.hpp"
#include <iostream>
#include <vector>
#include <cassert>

void testNeuralNetworkCreation() {
  std::vector<int> topology = {3, 2, 1};
  NeuralNetwork nn(topology);
  
  std::cout << "Testing NeuralNetwork creation:" << std::endl;
  assert(nn.getTopologySize() == 3);
  assert(nn.getLayers().size() == 3);
  assert(nn.getWeightMatrices().size() == 2);
  
  std::cout << "NeuralNetwork creation test passed.\n";
}

void testSetCurrentInput() {
  std::vector<int> topology = {3, 2, 1};
  NeuralNetwork nn(topology);
  
  std::vector<double> input = {1.0, 0.5, -1.0};
  nn.setCurrentInput(input);
  
  std::cout << "Testing setCurrentInput:" << std::endl;
  for (int i = 0; i < input.size(); i++) {
    assert(nn.getLayers().at(0)->getVal(i) == input.at(i));
    std::cout << "Layer[0] value " << i << ": " << nn.getLayers().at(0)->getVal(i) << std::endl;
  }
  
  std::cout << "setCurrentInput test passed.\n";
}

// void testPrintToConsole() {
//   std::vector<int> topology = {3, 2, 1};
//   NeuralNetwork nn(topology);

//   std::vector<double> input = {1.0, 0.5, -1.0};
//   nn.setCurrentInput(input);
  
//   std::cout << "Testing printToConsole:" << std::endl;

//   // Call printToConsole and allow it to print directly to std::cout
//   nn.printToConsole();
  
//   std::cout << "printToConsole test completed.\n";
// }

void testPrintWeightMatrix() {
  std::vector<int> topology = {3, 2, 1};
  NeuralNetwork nn(topology);

  std::vector<double> input = {1.0, 0.5, -1.0};
  nn.setCurrentInput(input);
  
  std::cout << "Testing printWeightMatrix:" << std::endl;

  std::cout<< "Matrix between layers 0 and 1 (3 x 2)" << endl;
  nn.printWeightMatrix(0);
  std::cout<< "Matrix between layers 1 and 2 (2 x 1)" << endl;
  nn.printWeightMatrix(1);
}

int main() {
  testNeuralNetworkCreation();
  testSetCurrentInput();
  // testPrintToConsole();
  testPrintWeightMatrix();

  std::cout << "All tests passed.\n";
  return 0;
}


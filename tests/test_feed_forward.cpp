// #include "NeuralNetwork.hpp"
// #include <iostream>
// #include <vector>
// #include <cassert>

// void testNeuralNetworkFeedForward() {
//   // Define the topology of the neural network
//   std::vector<int> topology = {3, 2, 1};
//   NeuralNetwork nn(topology);

//   // Manually initialize weights for testing
//   nn.setWeight(0, 0, 0, 0.5);  // Weight from neuron 0 in layer 0 to neuron 0 in layer 1
//   nn.setWeight(0, 1, 0, 0.3);  // Weight from neuron 1 in layer 0 to neuron 0 in layer 1
//   nn.setWeight(0, 2, 0, 0.2);  // Weight from neuron 2 in layer 0 to neuron 0 in layer 1
//   nn.setWeight(0, 0, 1, 0.4);  // Weight from neuron 0 in layer 0 to neuron 1 in layer 1
//   nn.setWeight(0, 1, 1, 0.7);  // Weight from neuron 1 in layer 0 to neuron 1 in layer 1
//   nn.setWeight(0, 2, 1, 0.9);  // Weight from neuron 2 in layer 0 to neuron 1 in layer 1
//   nn.setWeight(1, 0, 0, 1.0);  // Weight from neuron 0 in layer 1 to neuron 0 in layer 2
//   nn.setWeight(1, 1, 0, 1.5);  // Weight from neuron 1 in layer 1 to neuron 0 in layer 2

//   // Set the current input
//   std::vector<double> input = {1.0, 0.0, 1.0};
//   nn.setCurrentInput(input);

//   // Perform feed forward
//   nn.feedForward();

//   // Verify the values in the neurons of the last layer
//   std::cout << "Testing feedForward:" << std::endl;

//   // Print the values of the neurons in the output layer
//   Matrix* outputLayerMatrix = nn.getNeuronMatrix(topology.size() - 1);
//   outputLayerMatrix->printToConsole();

//   // Perform assertions (expected values depend on the weights and activation function)
//   // Note: Replace expected_value with the manually calculated value
//   // assert(outputLayerMatrix->getValue(0, 0) == expected_value);

//   delete outputLayerMatrix;

//   std::cout << "feedForward test completed.\n";
// }

// int main() {
//   testNeuralNetworkFeedForward();

//   std::cout << "All tests passed.\n";
//   return 0;
// }


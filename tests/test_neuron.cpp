#include <iostream>
#include <cassert>
#include "../include/Neuron.hpp"

void testNeuronActivation() {
  // Test neuron activation with positive value
  Neuron n1(2.0);
  assert(abs(n1.getActivatedVal() - 0.6667) < 0.0001); // 2 / (1 + 2) = 0.6667

  // Test neuron activation with negative value
  Neuron n2(-2.0);
  assert(abs(n2.getActivatedVal() + 0.6667) < 0.0001); // -2 / (1 + 2) = -0.6667

  // Test neuron activation with zero value
  Neuron n3(0.0);
  assert(abs(n3.getActivatedVal() - 0.0) < 0.0001); // 0 / (1 + 0) = 0.0

  std::cout << "Neuron activation test passed.\n";
}

void testNeuronDerivative() {
  // Test neuron derivative with positive value
  Neuron n1(2.0);
  assert(abs(n1.getDerivedVal() - (0.6667 * (1 - 0.6667))) < 0.0001);

  // Test neuron derivative with negative value
  Neuron n2(-2.0);
  assert(abs(n2.getDerivedVal() - (0.6667 * (1 - 0.6667))) < 0.0001);

  // Test neuron derivative with zero value
  Neuron n3(0.0);
  assert(abs(n3.getDerivedVal() - (0.0 * (1 - 0.0))) < 0.0001);

  std::cout << "Neuron derivative test passed.\n";
}

void testNeuronSetVal() {
  Neuron n(1.0);
  n.setVal(2.0);
  assert(abs(n.getVal() - 2.0) < 0.0001);
  assert(abs(n.getActivatedVal() - 0.6667) < 0.0001);
  assert(abs(n.getDerivedVal() - (0.6667 * (1 - 0.6667))) < 0.0001);

  std::cout << "Neuron set value test passed.\n";
}

int main() {
  testNeuronActivation();
  testNeuronDerivative();
  testNeuronSetVal();

  std::cout << "All tests passed.\n";
  return 0;
}


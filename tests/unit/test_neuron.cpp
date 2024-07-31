#include "../include/Neuron.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

void testNeuronActivation() {
  // Test neuron activation with positive value
  Neuron n1(2.0);
  double activatedVal = 2.0 / (1 + abs(2.0));
  std::cout << "Testing activation with positive value: " << n1.getActivatedVal() << std::endl;
  assert(abs(n1.getActivatedVal() - activatedVal) < 0.0001);

  // Test neuron activation with negative value
  Neuron n2(-2.0);
  activatedVal = -2.0 / (1 + abs(-2.0));
  std::cout << "Testing activation with negative value: " << n2.getActivatedVal() << std::endl;
  assert(abs(n2.getActivatedVal() - activatedVal) < 0.0001);

  // Test neuron activation with zero value
  Neuron n3(0.0);
  std::cout << "Testing activation with zero value: " << n3.getActivatedVal() << std::endl;
  assert(abs(n3.getActivatedVal() - 0.0) < 0.0001);

  std::cout << "Neuron activation test passed.\n";
}

void testNeuronDerivative() {
  // Test neuron derivative with positive value
  Neuron n1(2.0);
  double activatedVal = n1.getActivatedVal();
  std::cout << "Testing derivative with positive value: " << n1.getDerivedVal() << std::endl;
  assert(abs(n1.getDerivedVal() - (activatedVal * (1 - activatedVal))) < 0.0001);

  // Test neuron derivative with negative value
  Neuron n2(-2.0);
  activatedVal = n2.getActivatedVal();
  std::cout << "Testing derivative with negative value: " << n2.getDerivedVal() << std::endl;
  assert(abs(n2.getDerivedVal() - (activatedVal * (1 - activatedVal))) < 0.0001);

  // Test neuron derivative with zero value
  Neuron n3(0.0);
  activatedVal = n3.getActivatedVal();
  std::cout << "Testing derivative with zero value: " << n3.getDerivedVal() << std::endl;
  assert(abs(n3.getDerivedVal() - (activatedVal * (1 - activatedVal))) < 0.0001);

  std::cout << "Neuron derivative test passed.\n";
}

void testNeuronSetVal() {
  Neuron n(1.0);
  n.setVal(2.0);
  std::cout << "Setting neuron value to 2.0, activated value: " << n.getActivatedVal() << std::endl;
  assert(abs(n.getVal() - 2.0) < 0.0001);
  double activatedVal = n.getActivatedVal();
  std::cout << "Testing set value: " << n.getActivatedVal() << " " << n.getDerivedVal() << std::endl;
  assert(abs(n.getDerivedVal() - (activatedVal * (1 - activatedVal))) < 0.0001);

  std::cout << "Neuron set value test passed.\n";
}

int main() {
  testNeuronActivation();
  testNeuronDerivative();
  testNeuronSetVal();

  std::cout << "All tests passed.\n";
  return 0;
}


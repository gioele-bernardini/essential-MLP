#include "../include/Neuron.hpp"
#include <cmath>

// Constructor
Neuron::Neuron(double val) {
  this->val = val;

  activate();
  derive();
}

// Fast Sigmoid Function
// f(x) = x / (1 + |x|)
void Neuron::activate() {
  this->activatedVal = this->val / (1 + abs(this->val));
}

// Derivative for Fast Sigmoid Function
// f'(x) = f(x) * (1 - f(x))
void Neuron::derive() {
  this ->derivedVal = this->activatedVal * (1 - this->activatedVal);
}


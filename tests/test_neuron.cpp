#include "../include/Neuron.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  Neuron *n = new Neuron(0.9);

  cout << "Val: " << n->getVal() << endl;
  cout << "Activated Val: " << n->getActivatedVal() << endl;
  cout << "Derived Val: " << n->getDerivedVal() << endl;

  return 0;
}


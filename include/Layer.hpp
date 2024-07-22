#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>

using namespace std;

class Layer {
public:

  Layer(int size);
private:

  int size;
  vector<Neuron *> neurons;
};

#endif


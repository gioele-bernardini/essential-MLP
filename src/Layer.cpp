#include "Layer.hpp"

Layer::Layer(int size) {
  this->size = size;

  for (int i = 0; i < size; i++) {
    Neuron* n = new Neuron(0.00);
    this->neurons.push_back(n);
  }
}

void Layer::setVal(int i, double v) {
  this->neurons.at(i)->setVal(v);
}

double Layer::getVal(int i) {
  return this->neurons.at(i)->getVal();
}
  
vector<Neuron*> Layer::getNeurons() {
  return this->neurons;
}

Matrix* Layer::toMatrixVals() {
  Matrix* m = new Matrix(1, this->neurons.size(), false);

  for (int i = 0; i < this->neurons.size(); i++) {
    m->setValue(
      0,
      i,
      this->neurons.at(i)->getVal()
    );
  }

  return m;
}

Matrix* Layer::toMatrixActivatedVals() {
  Matrix* m = new Matrix(1, this->neurons.size(), false);

  for (int i = 0; i < this->neurons.size(); i++) {
    m->setValue(
      0,
      i,
      this->neurons.at(i)->getActivatedVal()
    );
  }

  return m;
}

Matrix* Layer::toMatrixDerivedVals() {
  Matrix* m = new Matrix(1, this->neurons.size(), false);

  for (int i = 0; i < this->neurons.size(); i++) {
    m->setValue(
      0,
      i,
      this->neurons.at(i)->getDerivedVal()
    );
  }

  return m;
}


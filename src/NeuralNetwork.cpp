#include "NeuralNetwork.hpp"
#include "Matrix.hpp"
#include "utils/MultiplyMatrix.hpp"
#include <vector>

NeuralNetwork::NeuralNetwork(vector<int> topology) {
  this->topology = topology;
  this->topologySize = topology.size();
  
  for (int i = 0; i < topologySize; i++) {
    Layer* l = new Layer(topology.at(i));
    this->layers.push_back(l);
  }

  // (topologySize -1) as the last Layer needs no such matrix
  for (int i = 0; i < (topologySize -1); i++) {
    Matrix* m = new Matrix(topology.at(i), topology.at(i +1), true);

    this->weightMatrices.push_back(m);
  }
}

void NeuralNetwork::setCurrentInput(vector<double> input) {
  this->input = input;

  for (int i = 0; i < input.size(); i++) {
    // Set the values in the layer [0] (input layer)
    this->layers.at(0)->setVal(i, input.at(i));
  }
}

void NeuralNetwork::printToConsole() {
  for (int i = 0; i < this->layers.size(); i++) {
    cout << "LAYER: " << i << endl;

    // First layer (input)
    if (i == 0) {
      Matrix* m = this->layers.at(i)->toMatrixVals();
      m->printToConsole();
      delete m;
    } else {
      Matrix* m = this->layers.at(i)->toMatrixActivatedVals();
      m->printToConsole();
      delete m;
    }
  }
}

void NeuralNetwork::printWeightMatrix(int i) {
  this->weightMatrices.at(i)->printToConsole();
}

// Feed Forward algorithm
void NeuralNetwork::feedForward() {
  for (int i = 0; i < (this->layers.size() - 1); i++) {
    // Get the neuron matrix for the current layer
    Matrix* a = this->getNeuronMatrix(i);

    // If not the input layer, get the activated neuron matrix
    if (i != 0) {
      delete a; // Delete the previous matrix to prevent memory leak
      a = this->getActivatedNeuronMatrix(i);
    }

    // Get the weight matrix for the current layer
    Matrix* b = this->getWeightMatrix(i);

    // Multiply the matrices a and b
    utils::MultiplyMatrix multiplyMatrix(a, b);
    Matrix* c = multiplyMatrix.execute();

    // Set the values in the next layer's neurons
    for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
      this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index));
    }

    // Clean up memory
    delete a;
    delete c;
  }
}

void NeuralNetwork::setErrors() {
  if (this->target.size() == 0) {
    cerr << "No target for this neural network" << endl;
    assert(false);
  }

  if (this->target.size() != this->layers.at(this->layers.size() -1)->getNeurons().size()) {
    cerr << "Target size is not the same as output layer size: " << this->layers.at(this->layers.size() -1)->getNeurons().size() << endl;
    assert(false);
  }

  // Initialize the errors vector
  errors.resize(this->target.size());

  this->error = 0.00;
  int outputLayerIndex = this->layers.size() -1;
  vector<Neuron*> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();

  for (int i = 0; i < target.size(); i++) {
    double tempErr = (outputNeurons.at(i)->getActivatedVal() - target.at(i));
    errors.at(i) = tempErr;
    this->error += tempErr;
  }

  historicalErrors.push_back(this->error);
}

void NeuralNetwork::backPropagation() {
  vector<Matrix*> newWeights;
  Matrix* gradients;

  // Output to hidden
  int outputLayerIndex = this->layers.size() - 1;
  Matrix* derivedValuesYToZ = this->layers.at(outputLayerIndex)->toMatrixDerivedVals();

  // Matrix for the gradients, isRandom false just for good practice
  Matrix* gradientsYToZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);

  for (int i = 0; i < this->errors.size(); i++) {
    double d = derivedValuesYToZ->getValue(0, i);
    double e = this->errors.at(i);
    double g = d * e;

    gradientsYToZ->setValue(0, i, g);
  }

  int lastHiddenLayerIndex = outputLayerIndex - 1;
  Layer* lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);

  // Matrices
  Matrix* weightsOutputHidden = this->weightMatrices.at(outputLayerIndex - 1);

  Matrix* deltaOutputHidden = (new utils::MultiplyMatrix(
    gradientsYToZ->transpose(),
    lastHiddenLayer->toMatrixActivatedVals())
  )->execute()->transpose();

  Matrix* newWeightsOutputToHidden = new Matrix(
    deltaOutputHidden->getNumRows(),
    deltaOutputHidden->getNumCols(),
    false
  );

  for (int r = 0; r < deltaOutputHidden->getNumRows(); r++) {
    for (int c = 0; c < deltaOutputHidden->getNumCols(); c++) {
      double originalWeight = weightsOutputHidden->getValue(r, c);
      double deltaWeight = deltaOutputHidden->getValue(r, c);

      newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight));
    }
  }

  newWeights.push_back(newWeightsOutputToHidden);
  // WATCH OUT HERE
  gradients = new Matrix(
    gradientsYToZ->getNumRows(), gradientsYToZ->getNumCols(),
    false
  );
  for (int r = 0; r < gradientsYToZ->getNumRows(); r++) {
    for (int c = 0; c < gradientsYToZ->getNumCols(); c++) {
      gradients->setValue(r, c, gradientsYToZ->getValue(r, c));
    }
  }

  // Moving from last hidden layer down to input layer
  for (int i = outputLayerIndex -1; i >= 0; i--) {
    Layer* l = this->layers.at(i);
    Matrix* derivedHidden = l->toMatrixDerivedVals();

    Matrix* derivedGradients = new Matrix(
      1,
      l->getNeurons().size(),
      false
    );

    Matrix* weightMatrix = this->weightMatrices.at(i);

    for (int r = 0; r < weightMatrix->getNumRows(); r++) {
      for (int c = 0; c < weightMatrix->getNumCols(); c++) {
        
      }
    }
  }
}

Matrix* NeuralNetwork::getNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixVals();
}

Matrix* NeuralNetwork::getActivatedNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixActivatedVals();
}

Matrix* NeuralNetwork::getDerivedNeuronMatrix(int i) {
  return this->layers.at(i)->toMatrixDerivedVals();
}

Matrix* NeuralNetwork::getWeightMatrix(int i) {
  return this->weightMatrices.at(i);
}


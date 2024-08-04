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
  vector<Matrix*> newWeights; // Vector to store updated weights after backpropagation
  Matrix* gradient; // Matrix to store gradients during backpropagation

  // Output to hidden
  int outputLayerIndex = this->layers.size() - 1; // Index of the output layer
  Matrix* derivedValuesYToZ = this->layers.at(outputLayerIndex)->toMatrixDerivedVals(); // Derived values of the output layer

  // Matrix for the gradients, isRandom false just for good practice
  Matrix* gradientsYToZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false); // Gradient matrix initialization

  // Calculate gradients for the output layer
  for (int i = 0; i < this->errors.size(); i++) {
    double d = derivedValuesYToZ->getValue(0, i); // Get derived value
    double e = this->errors.at(i); // Get error for the neuron
    double g = d * e; // Compute gradient

    gradientsYToZ->setValue(0, i, g); // Set gradient value in the matrix
  }

  int lastHiddenLayerIndex = outputLayerIndex - 1; // Index of the last hidden layer
  if (lastHiddenLayerIndex >= 0) {
    Layer* lastHiddenLayer = this->layers.at(lastHiddenLayerIndex); // Last hidden layer object

    // Matrices
    Matrix* weightsOutputHidden = this->weightMatrices.at(outputLayerIndex - 1); // Weights between the last hidden layer and output layer

    // Compute delta (weight updates) for weights between the output layer and last hidden layer
    Matrix* deltaOutputHidden = (new utils::MultiplyMatrix(
      gradientsYToZ->transpose(),
      lastHiddenLayer->toMatrixActivatedVals())
    )->execute()->transpose();

    // Create a matrix to store updated weights between output and last hidden layer
    Matrix* newWeightsOutputToHidden = new Matrix(
      deltaOutputHidden->getNumRows(),
      deltaOutputHidden->getNumCols(),
      false
    );

    // Update weights by subtracting the delta
    for (int r = 0; r < deltaOutputHidden->getNumRows(); r++) {
      for (int c = 0; c < deltaOutputHidden->getNumCols(); c++) {
        double originalWeight = weightsOutputHidden->getValue(r, c); // Get current weight
        double deltaWeight = deltaOutputHidden->getValue(r, c); // Get delta weight

        newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight)); // Update weight
      }
    }

    newWeights.push_back(newWeightsOutputToHidden); // Store the updated weights
  }

  gradient = new Matrix(
    gradientsYToZ->getNumRows(), gradientsYToZ->getNumCols(),
    false
  );
  for (int r = 0; r < gradientsYToZ->getNumRows(); r++) {
    for (int c = 0; c < gradientsYToZ->getNumCols(); c++) {
      gradient->setValue(r, c, gradientsYToZ->getValue(r, c)); // Copy gradients for further backpropagation
    }
  }

  // Moving from last hidden layer down to input layer
  for (int i = outputLayerIndex - 1; i >= 0; i--) {
    Layer* l = this->layers.at(i); // Current layer
    Matrix* derivedHidden = l->toMatrixDerivedVals(); // Derived values of current layer
    Matrix* activatedHidden = l->toMatrixActivatedVals(); // Activated values of current layer

    Matrix* derivedGradients = new Matrix(
      1,
      l->getNeurons().size(),
      false
    );

    Matrix* weightMatrix = this->weightMatrices.at(i); // Weights between the current and next layer
    if (i - 1 >= 0) {
      Matrix* originalWeight = this->weightMatrices.at(i - 1); // Weights between the previous layers

      // Compute the gradients for the hidden layers
      for (int r = 0; r < weightMatrix->getNumRows(); r++) {
        double sum = 0.00;
        for (int c = 0; c < weightMatrix->getNumCols(); c++) {
          // Debug prints for tracking index values and matrix sizes
          std::cout << "r: " << r << ", c: " << c << std::endl;
          std::cout << "gradient->getNumCols(): " << gradient->getNumCols() << std::endl;
          std::cout << "weightMatrix->getNumRows(): " << weightMatrix->getNumRows() << std::endl;
          std::cout << "weightMatrix->getNumCols(): " << weightMatrix->getNumCols() << std::endl;

          if (r < gradient->getNumCols() && r >= 0 && c >= 0 && c < weightMatrix->getNumCols()) {
            double p = gradient->getValue(0, r) * weightMatrix->getValue(r, c); // Gradient * weight
            sum += p;
          } else {
            std::cout << "Indice fuori dai limiti: r = " << r << ", c = " << c << std::endl;
          }
        }

        double g = sum * activatedHidden->getValue(0, r); // Multiply by the activation of the neuron
        derivedGradients->setValue(0, r, g); // Store the computed gradient
      }

      // Get the activations of the previous layer or the input layer
      Matrix* leftNeurons = (i - 1) == 0 ? this->layers.at(0)->toMatrixVals() : this->layers.at(i - 1)->toMatrixActivatedVals();

      // Compute the weight deltas
      Matrix* deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(), leftNeurons))->execute()->transpose();
      Matrix* newWeightsHidden = new Matrix(
        deltaWeights->getNumRows(),
        deltaWeights->getNumCols(),
        false
      );

      // Update the weights for the hidden layers
      for (int r = 0; r < newWeightsHidden->getNumRows(); r++) {
        for (int c = 0; c < newWeightsHidden->getNumCols(); c++) {
          double w = originalWeight->getValue(r, c); // Get current weight
          double d = deltaWeights->getValue(r, c); // Get delta weight

          double n = w - d; // Update weight
          newWeightsHidden->setValue(r, c, n); // Set the updated weight
        }
      }

      newWeights.push_back(newWeightsHidden);
    }

    gradient = new Matrix(
      derivedGradients->getNumRows(), gradientsYToZ->getNumCols(),
      false
    );
    for (int r = 0; r < derivedGradients->getNumRows(); r++) {
      for (int c = 0; c < derivedGradients->getNumCols(); c++) {
        gradient->setValue(r, c, derivedGradients->getValue(r, c)); // Update gradient for next layer
      }
    }
  }

  cout << "Done with back prop" << endl;
  cout << "New Weights size: " << newWeights.size() << endl;
  cout << "Old Weights size: " << this->weightMatrices.size() << endl;

  reverse(newWeights.begin(), newWeights.end());
  this->weightMatrices = newWeights;
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


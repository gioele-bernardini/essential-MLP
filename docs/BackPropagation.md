### Backpropagation Algorithm

The backpropagation algorithm is an essential part of training neural networks. It allows the network to adjust its weights based on the error of its output, ultimately learning from the data it processes. Below is a more detailed breakdown of how the algorithm works and its implementation in the provided code.

#### Introduction to Backpropagation

Backpropagation stands for "backward propagation of errors," and it's used to minimize the error in the network's predictions by adjusting the weights of the neurons. This is done using the gradient descent optimization technique, which seeks to find the minimum of the error function (often referred to as the loss or cost function).

#### Steps of the Backpropagation Algorithm

1. **Forward Pass:**
   - The network takes an input and passes it forward through each layer. Each neuron in a layer receives inputs, multiplies them by corresponding weights, sums them up, and applies an activation function to produce its output. The outputs of one layer become the inputs for the next layer.
   - The final layer's output is the network's prediction, which is compared to the target value to compute the error.

2. **Error Calculation:**
   - The error is calculated as the difference between the network's output and the actual target value. This difference is used to measure how well the network performed. In many cases, the Mean Squared Error (MSE) is used, which is the average of the squares of the differences between the predicted and actual values.

3. **Backward Pass (Backpropagation):**
   - During the backward pass, the goal is to determine how to change the weights to reduce the error. This involves calculating the gradient of the error with respect to each weight. The gradient tells us how much the error would change if we adjusted the weight slightly.
   - The backpropagation algorithm calculates these gradients layer by layer, starting from the output layer and moving backwards to the input layer.

#### Detailed Implementation Explanation

Let's delve deeper into the code you provided to understand how backpropagation is implemented.

1. **Gradient Calculation for the Output Layer:**

   The gradient is calculated using the chain rule from calculus. For each neuron, the gradient of the error with respect to the neuron's output is calculated as:

   \[
   \delta = \text{activation derivative} \times \text{error}
   \]

   - **Activation Derivative:** This is the derivative of the activation function used in the neuron (e.g., sigmoid, ReLU). It determines how much the output of the neuron changes with respect to its input. In mathematical terms, if the activation function is \( f(z) \), its derivative \( f'(z) \) is used to scale the error.
   - **Error:** The error term for a neuron in the output layer is simply the difference between the neuron's output and the target value.

   In the code:

   ```cpp
   for (int i = 0; i < this->errors.size(); i++) {
     double d = derivedValuesYToZ->getValue(0, i); // Activation derivative
     double e = this->errors.at(i); // Neuron error
     double g = d * e; // Gradient
     gradientsYToZ->setValue(0, i, g); // Store the calculated gradient
   }
   ```

   Here, `derivedValuesYToZ` holds the derivative of the activation function values, and `errors` holds the difference between the predicted and target values.

2. **Weight Updates for Output Layer:**

   The calculated gradients are used to determine how the weights should be adjusted. The weight adjustment (often called delta weights) is calculated as:

   \[
   \Delta w = \eta \times \delta \times \text{input}
   \]

   Where:
   - \( \eta \) (eta) is the learning rate, a small value that controls how much the weights are adjusted.
   - \( \delta \) is the gradient we calculated earlier.
   - The input is the output from the previous layer.

   The weights are then updated by subtracting the delta weights:

   ```cpp
   Matrix* deltaOutputHidden = (new utils::MultiplyMatrix(
     gradientsYToZ->transpose(),
     lastHiddenLayer->toMatrixActivatedVals())
   )->execute()->transpose();
   ```

   This part of the code multiplies the gradients with the activated outputs of the last hidden layer to calculate the deltas for the weights. The weights are then updated by subtracting these deltas from the current weights:

   ```cpp
   newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight));
   ```

3. **Backpropagating Gradients through Hidden Layers:**

   Once the output layer's weights are updated, the algorithm moves backwards through the hidden layers. The gradients for each hidden layer are calculated using the chain rule again. The error in the hidden layer is not directly available, so it is computed by considering the gradients and weights of the layer above (i.e., the layer closer to the output).

   ```cpp
   for (int i = outputLayerIndex - 1; i >= 0; i--) {
     Layer* l = this->layers.at(i);
     Matrix* derivedHidden = l->toMatrixDerivedVals();
     Matrix* activatedHidden = l->toMatrixActivatedVals();

     Matrix* derivedGradients = new Matrix(1, l->getNeurons().size(), false);

     Matrix* weightMatrix = this->weightMatrices.at(i);
     for (int r = 0; r < weightMatrix->getNumRows(); r++) {
       double sum = 0.00;
       for (int c = 0; c < weightMatrix->getNumCols(); c++) {
         if (r < gradient->getNumCols()) {
           double p = gradient->getValue(0, r) * weightMatrix->getValue(r, c);
           sum += p;
         }
       }
       double g = sum * activatedHidden->getValue(0, r);
       derivedGradients->setValue(0, r, g);
     }
   ```

   This segment of code shows how the algorithm calculates the gradients for each hidden layer by summing up the contributions from the layer above. It multiplies the gradients from the upper layer with the corresponding weights and then multiplies the result by the activation derivative of the current layer.

4. **Final Weight Update:**

   After the gradients are propagated through all the layers, the new weights are calculated and applied to the network. The old weights are replaced with the updated ones, and the network is ready for the next training iteration.

   ```cpp
   reverse(newWeights.begin(), newWeights.end());
   this->weightMatrices = newWeights;
   ```

   This ensures that the updated weights are applied correctly in reverse order, moving from the last hidden layer back to the input layer.

#### Summary

The backpropagation algorithm in this code performs the following steps:
- **Forward Pass:** The network processes the input to generate an output.
- **Error Calculation:** The error is computed by comparing the output to the target.
- **Backward Pass:** The error is propagated back through the network, calculating gradients and adjusting weights accordingly.
- **Weight Update:** The weights are updated in such a way that the network's error is minimized over time.

This process is repeated across multiple iterations (epochs) during training until the network's error is minimized to an acceptable level. The backpropagation algorithm is crucial in enabling neural networks to learn from data, making it a foundational technique in the field of machine learning.


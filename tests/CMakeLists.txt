# CMake configuration for tests

# Add the executable for the tests
add_executable(test_neuron test_neuron.cpp)
add_executable(test_matrix test_matrix.cpp)
add_executable(test_neural_network test_neural_network.cpp)

# Link the test executables with the main library
target_link_libraries(test_neuron essential-MLP-lib)
target_link_libraries(test_matrix essential-MLP-lib)
target_link_libraries(test_neural_network essential-MLP-lib)

# Add the tests
add_test(NAME TestNeuron COMMAND test_neuron)
add_test(NAME TestMatrix COMMAND test_matrix)
add_test(NAME TestNeuralNetwork COMMAND test_neural_network)


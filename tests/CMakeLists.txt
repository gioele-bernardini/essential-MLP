# CMake configuration for tests

# Add the executables for unit tests
add_executable(test_neuron unit/test_neuron.cpp)
add_executable(test_matrix unit/test_matrix.cpp)
add_executable(test_neural_network unit/test_neural_network.cpp)

# Add the executable for integration tests
add_executable(test_integration integration/test_integration.cpp)

# Link the unit test executables with the main library
target_link_libraries(test_neuron essential-MLP-lib)
target_link_libraries(test_matrix essential-MLP-lib)
target_link_libraries(test_neural_network essential-MLP-lib)

# Link the integration test executable with the main library
target_link_libraries(test_integration essential-MLP-lib)

# Add the unit tests
add_test(NAME TestNeuron COMMAND test_neuron)
add_test(NAME TestMatrix COMMAND test_matrix)
add_test(NAME TestNeuralNetwork COMMAND test_neural_network)

# Add the integration tests
add_test(NAME TestIntegration COMMAND test_integration)


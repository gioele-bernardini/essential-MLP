# CMake configuration for tests

# Add the executable for the tests
add_executable(test_neuron test_neuron.cpp)

# Link the test executable with the main library
target_link_libraries(test_neuron essential-MLP-lib)

# Add the tests
add_test(NAME TestNeuron COMMAND test_neuron)


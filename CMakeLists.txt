cmake_minimum_required(VERSION 3.0)
project(essential-MLP)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add the library
add_library(essential-MLP-lib
  src/Neuron.cpp
  src/Layer.cpp
  src/Matrix.cpp
  src/NeuralNetwork.cpp
  src/utils/MatrixToVector.cpp
  src/utils/MultiplyMatrix.cpp
)

# Add the executable
add_executable(essential-MLP
  src/main.cpp
)

# Link the executable with the library
# Tell to link the library with the executable
target_link_libraries(essential-MLP essential-MLP-lib)

# Enable testing
enable_testing()

# Add the tests directory
add_subdirectory(tests)


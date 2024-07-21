cmake_minimum_required(VERSION 3.0)
project(essential-MLP)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(essential-MLP
  src/main.cpp
  src/Neuron.cpp
)


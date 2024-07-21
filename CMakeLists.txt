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
)

# Add the executable
add_executable(essential-MLP
  src/main.cpp
)

# Link the executable with the library
target_link_libraries(essential-MLP essential-MLP-lib)

# Enable testing
enable_testing()

# Add the tests directory
add_subdirectory(tests)


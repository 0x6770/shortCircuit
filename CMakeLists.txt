cmake_minimum_required(VERSION 3.0.0)
project(short_circuit VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11) # enable C++ 11 feature

include(CTest)
enable_testing()

# main executable 
add_executable(short_circuit main.cpp src/circuit.cpp src/component.cpp src/linear_components.cpp src/nonlinear_components.cpp src/node.cpp src/parser.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

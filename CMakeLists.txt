cmake_minimum_required(VERSION 3.0.0)
project(short_circuit VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11) # enable C++ 11 feature

# ---------------------------------------------------------------------------------------
# Inlcude .hpp files in include/
# ---------------------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(EIGEN ./extern/eigen/CORE ./extern/eigen/DENSE)
set(SPDLOG ./extern/spdlog/spdlog.h ./extern/spdlog/common.h ./extern/spdlog/sinks/basic_file_sink.h)
set(SOURCES ./src/circuit.cpp ./src/component.cpp ./src/linear_components.cpp ./src/node.cpp ./src/nonlinear_components.cpp ./src/parser.cpp)
set(HEADERS ./include/circuit.hpp ./include/component.hpp ./include/linear_components.hpp ./include/node.hpp ./include/nonlinear_components.hpp ./include/parser.hpp)

# ---------------------------------------------------------------------------------------
# Google Test
# ---------------------------------------------------------------------------------------
# Download and unpack googletest at configure time
configure_file(./CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# ---------------------------------------------------------------------------------------
# CTest
# ---------------------------------------------------------------------------------------
include(CTest)
enable_testing()
# Parser
add_executable(test_parser ./test/test_parser.cpp ${SOURCES} ${HEADERS})
target_link_libraries(test_parser gtest_main)
add_test(NAME test_parser COMMAND test_parser)
# Node
add_executable(test_node ./test/test_node.cpp ${SOURCES} ${HEADERS})
target_link_libraries(test_node gtest_main)
add_test(NAME test_node COMMAND test_node)
# Resistor
add_executable(test_resistor ./test/test_resistor.cpp ${SOURCES} ${HEADERS})
target_link_libraries(test_resistor gtest_main)
add_test(NAME test_resistor COMMAND test_resistor)
# Capacitor
add_executable(test_capacitor ./test/test_capacitor.cpp ${SOURCES} ${HEADERS})
target_link_libraries(test_capacitor gtest_main)
add_test(NAME test_capacitor COMMAND test_capacitor)
# Inductor
add_executable(test_inductor ./test/test_inductor.cpp ${SOURCES} ${HEADERS})
target_link_libraries(test_inductor gtest_main)
add_test(NAME test_inductor COMMAND test_inductor)

# ---------------------------------------------------------------------------------------
# Main executable 
# ---------------------------------------------------------------------------------------
add_executable(short_circuit main.cpp ${SOURCES} ${HEADERS} ${EIGEN} ${SPDLOG})

if(SPDLOG_BUILD_EXAMPLE_HO)
    target_link_libraries(short_circuit PRIVATE spdlog::spdlog_header_only)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

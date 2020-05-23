#!/bin/bash

set -e

g++ -std=c++0x circuit.cpp main_test.cpp node.cpp component.cpp -o test_output
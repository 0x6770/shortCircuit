#!/bin/bash

set -e

g++ -std=c++0x circuit.cpp Component.cpp node.cpp parser.cpp transient.cpp test.cpp -o test_program

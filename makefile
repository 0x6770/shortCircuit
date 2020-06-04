CXX			= g++
CXX_FLAGS   = -Wall -Wextra -std=c++11 -ggdb

SRC         = src
BIN     	= bin
INCLUDE 	= include
TEST		= test
LIBRARIES   =
LIB 		= lib
EXECUTABLE  = main

bold=$(tput bold)
normal=$(tput sgr0)

all: 
	@echo "\033[1mCompile and run \033[0m"
	@echo "=============================="
	@echo "make run net=< input_file in input/ >"
	@echo "\033[1mExample\033[0m: make run net=test_input"
	@echo "\n"
	@echo "\033[1mTest \033[0m"
	@echo "=============================="
	@echo "make test test_target=< test_file in test />"
	@echo "\033[1mExample\033[0m: make test test_target=test_circuit"
	@echo "\n"
	@echo "\033[1mGenerate output file \033[0m"
	@echo "=============================="
	@echo "make output net=< input_file in input/ >"
	@echo "\033[1mExample\033[0m: make output net=test_input_Capacitor"
	@echo "\n"
	@echo "\033[1mClean \033[0m"
	@echo "=============================="
	@echo "make clean"
	@echo "All the binaries created is stored in bin/, you can run this command to delete them."
	@echo "The .gitignore file in /bin ensures no binarty file will be synced by git so no worry if you forget to run this command."

run: clean $(BIN)/$(EXECUTABLE)
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE) ./input/$(net).net

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp ./main.cpp
	@echo "🚧 Compiling..."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

test: clean  $(SRC)/*.cpp ./$(TEST)/$(test_target).cpp
	@echo "🚧 Testing..."  ./$(TEST)/$(test_target)
	@echo "🚧 Compiling..."  ./$(TEST)/$(test_target)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(SRC)/*.cpp ./$(TEST)/$(test_target).cpp -o ./$(BIN)/$(test_target)
	@echo "🚀 Executing..." ./$(BIN)/$(test_target)
	./$(BIN)/$(test_target)

output: clean $(BIN)/$(EXECUTABLE)
	clear
	@echo "🚀 Generating output file..."
	./$(BIN)/$(EXECUTABLE) ./input/$(net).net > simdata.txt

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/*

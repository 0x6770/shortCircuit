CXX			= g++
CXX_FLAGS   = -Wall -Wextra -std=c++11 -ggdb

SRC         = src
BIN     	= bin
INCLUDE 	= include
TEST		= test
LIBRARIES   =
LIB 		= lib
EXECUTABLE  = main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE) ./input/$(net).net

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp ./main.cpp
	@echo "🚧 Compiling..."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

test: clean  $(SRC)/*.cpp ./$(TEST)/$(test_target).cpp
	@echo "🚧 Testing..."  ./$(TEST)/$(test_target)
	@echo "🚧 Compiling..."  ./$(TEST)/$(test_target)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(SRC)/*.cpp ./$(TEST)/$(test_target).cpp -o ./$(BIN)/$(test_target)
	@echo "🚀 Executing..." ./$(BIN)/$(test_target)
	./$(BIN)/$(test_target)

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/*

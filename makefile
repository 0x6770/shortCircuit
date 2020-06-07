all: 
	@clear
	@echo "\n"
	@echo "\033[1m🚀 Build\033[0m"
	@echo "=============================="
	@echo "$$ make run"
	@echo "This command creates a build/ folder if it has not been created. Then CMake will configure the project. An executable will be produced at ./build/short_circuit"
	@echo "\n"
	@echo "\033[1m🏗 Rebuild\033[0m"
	@echo "=============================="
	@echo "$$ make rebuild"
	@echo "This command removes the previous build/ folder and compiles the project again. An executable will be produced at ./build/short_circuit"
	@echo "\n"
	@echo "\033[1m🚧 Test \033[0m"
	@echo "=============================="
	@echo "$$ make test"
	@echo "\033[1mExample\033[0m: make test test_target=test_circuit"
	@echo "\n"
	@echo "\033[1m🧹 Clean\033[0m"
	@echo "=============================="
	@echo "$$ make clean"
	@echo "All the binaries created are stored in build/, you can run this command to clean them."
	@echo "\n"

run: 
	@echo "\n\n🚀 Building short_circuit..."
ifneq ($(wildcard ./build/),)
	@echo "build/ exists"
	@cd build && make -j
else
	@echo "build/ does not exist"
	@mkdir build && cd build && cmake .. && make -j
endif
	@echo "🚀 short_circuit is ready to rock"
	@echo "\n\n\tTry $$ ./build/short_circuit [path to input file]"
	@echo "\n\n"

delete:
	@echo "\n\n🧼 Removing previous build/ folder..."
	-rm -rf ./build

test: run
	@echo "🚧 Testing short_circuit..."
ifneq ($(wildcard ./build/),)
	@echo "found build/\n\n"
	./build/test_parser
	./build/test_node
	./build/test_resistor
	./build/test_capacitor
	./build/test_inductor
else
	@echo "build/ not found\n\n"
endif

clean:
ifneq ($(wildcard ./build/),)
	@echo "\n\n🧹 Start cleaning build/..."
	@cd build && make clean
	@echo "✨ build/ is clean now\n\n"
else
	@echo "⚠️  build/ does not exist, not need to clean\n\n"
endif

all: 
	@clear
	@echo -e "\n"
	@echo -e "\033[1m🚀 Build\033[0m"
	@echo -e "=============================="
	@echo -e "$$ make run"
	@echo -e "This command creates a build/ folder if it has not been created. Then CMake will configure the project. An executable will be produced at ./build/short_circuit"
	@echo -e "\n"
	@echo -e "\033[1m🏗  Delete\033[0m"
	@echo -e "=============================="
	@echo -e "$$ make delete"
	@echo -e "This command removes the previous build/ folder and compiles the project again. An executable will be produced at ./build/short_circuit"
	@echo -e "\n"
	@echo -e "\033[1m🚧 Test \033[0m"
	@echo -e "=============================="
	@echo -e "$$ make test"
	@echo -e "\033[1mExample\033[0m: make test test_target=test_circuit"
	@echo -e "\n"
	@echo -e "\033[1m🧹 Clean\033[0m"
	@echo -e "=============================="
	@echo -e "$$ make clean"
	@echo -e "All the binaries created are stored in build/, you can run this command to clean them."
	@echo -e "\n"

run: 
	@echo -e "\n\n🚀 Building short_circuit..."
ifneq ($(wildcard ./build/),)
	@echo -e "build/ exists"
	@cd build && make -j
else
	@echo -e "build/ does not exist"
	@mkdir build && cd build && cmake .. && make
endif
	@echo -e "🚀 short_circuit is ready to rock"
	@echo -e "\n\n\tTry $$ ./build/short_circuit [path to input file]"
	@echo -e "\n\n"

delete:
	@echo -e "\n\n🧼 Removing previous build/ folder..."
	-rm -rf ./build

test: run
	@echo -e "🚧 Testing short_circuit..."
ifneq ($(wildcard ./build/),)
	@echo -e "found build/\n\n"
	./build/test_parser
	./build/test_node
	./build/test_resistor
	./build/test_capacitor
	./build/test_inductor
else
	@echo -e "build/ not found\n\n"
endif

clean:
ifneq ($(wildcard ./build/),)
	@echo -e "\n\n🧹 Start cleaning build/..."
	@cd build && make clean
	@echo -e "✨ build/ is clean now\n\n"
else
	@echo -e "⚠️  build/ does not exist, not need to clean\n\n"
endif

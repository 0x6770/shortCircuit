# Short Circuit

A SPICE-like circuit simulator. 

### Features

-   Run transient simulation of a given circuit involving
    -   Resistor
    -   Capacitor
    -   Inductor
    -   Voltage source (DC, SIN)
    -   Current source
    -   Diode **(TODO)**
    -   Transistor **(TODO)**
-   Output voltage at every node, current flow through every component

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/short_circuit8lyp7r.png" alt="short_circuit" style="zoom:33%;" />

### How to Build

Following commands generating makefile by `cmake` and then compiling the makefile by `make`. 

```bash
git clone https://github.com/Ouikujie/shortCircuit
cd shortCircuit && mkdir build && cd build
cmake .. && make -j # -j flag allows multiple jobs been done at once
```

An executable file will be produced at `./build/short_circuit`.

#### Build requirements

-   [CMake](https://cmake.org/) 
-   A compiler that support C++11 standard



### How to run

```bash
./short_circuit [path to input file] > [path to output file]
```

#### Example

```
./build/short_circuit ./input/sin_D.net > ./simdata.txt
```



### Structure

```bash
.
├── CMakeLists.txt
├── README.md
├── input/ # contains various .net input files
├── main.cpp
├── include
│   ├── circuit.hpp
│   ├── component.hpp
│   ├── linear_components.hpp
│   ├── node.hpp
│   ├── nonlinear_components.hpp
│   └── parser.hpp
└── src
    ├── circuit.cpp
    ├── component.cpp
    ├── linear_components.cpp
    ├── node.cpp
    ├── nonlinear_components.cpp
    └── parser.cpp
```


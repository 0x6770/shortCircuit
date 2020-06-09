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
make run
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



## Verification and Validation

Software verification and validation is the process of checking that a software system meets specifications and that it fulfils its intended purpose. [9] The role of testing increased in the manufacture, electronics, and communication software industries where innovative and redesign takes place to gain the customer satisfaction and meet the competitive nature. The testing is most widely used approach to ensure the quality of the software that the designers have built. [10] This process was done by taking various test cases and performed transient simulation of the test circuits. Edge cases were also considered to find the limitations of the circuit simulator. After that, comparisons were done between the graphs from the software program and the graphs from LTSpice.

All the test inputs mentioned in this section can be found in the `test/` directory in the Github repository [repo].

All the tests were conducted by the same executable file [executable file] as controlled variable.

#### Unit test

To ensure the functional requirements are met after every change to the source files, a set of unit tests are created covering every class and every member function. With the help of CTest and Google Test, these tests are managed to  be run with a single command `make test` and an overall report will be produced to terminal.

In the test file, both normal output and error prompt are handled.

```c++
TEST(capacitor_test, capacitor_contain_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_TRUE(C->contain_node("p"));
    EXPECT_FALSE(C->contain_node("c"));
}

TEST(parser_test, parser_parse_number)
{
    vector<string> numbers_string2 = {"", "k", "a"};
    for (int i = 0; i < numbers_string2.size(); i++)
    {
        ASSERT_DEATH(parse_number(numbers_string2[i]), "Assert|ERROR") << numbers_string2[i];
    }
}
```

By inspecting the code, one anomaly is found particularly wired, though the program is designed to be compatible with different platforms, the parse_number() function does not work properly with gcc 9.3.0 on MacOS. As mentioned in the previous section, the parse_number() function is in charge of translate text descriptions like 1k, 1Meg, 1p, into corresponding numeric equivalent. 

```c++
double parse_number(string input)
{
    double result = 0.0;
    string multiplier = "";

    stringstream ss(input);
    ss >> result >> multiplier;
    ...
}
```

When compiled with gcc 9.3.0 on MacOS, the program is not able to separate number and multiplier for multiplier "p" and "n". One hypothesis is that this anomaly might due to text encoding on MacOS. This error does not occur on the other two major test platforms we use, Ubuntu and Arch linux.

#### Accuracy compare to LTSPICE

This test is designed to justify the accuracy of the simulation result of the target program. As reference, the result from LTSPICE running the same input file is used for comparison. With the interest to have a general comparison about all available component models in the program 

```net
* test input for RCL with sinusoidal voltage
V1 N001 0 SINE(0 10 1k)
R1 N002 N001 100
R2 N003 0 50
C1 N002 N003 1µ
L1 N002 N003 50m
.tran 0 4m 0 1u
.backanno
.end
```

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_current_refsPTeo6.png" alt="CLR_simulation_current_ref" style="zoom:50%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_currentCzKiAk.png" alt="CLR_simulation_current" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_voltage_refjMTaPW.png" alt="CLR_simulation_voltage_ref" style="zoom:50%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_voltageGwoBQPxs2Ivj.png" alt="CLR_simulation_voltage" style="zoom:50%;" />

Numeric analysis was suggested at the first place during group discussion but the viable time step solver feature of LTSpice causing the reference data set to have a different size than the target one and therefore make direct comparison of the Euclidean distance impossible. Graphical comparison was then proposed and used.

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/comparison_I%28L1%293eyroZ.png" alt="comparison_I(L1)" style="zoom:50%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/comparison_VN0025N8JQs.png" alt="comparison_VN002" style="zoom:50%;" />

As the above figures show, the main deviation occurs at the start of the simulation. 

#### Time Complexity

Following are the results from a series of tests that were conducted with different numbers of a single type of components each time. These tests are all conducted using the same executable file and the same docker container running on Arch Linux with 2.5 gigabytes free memory and 4 CPU cores. In order to minimise the potential turbulence caused by background processes and core temperature, etc, each input file was tested for five time to find the average execution time. 

```bash
#!/bin/bash
set -e

short_circuit=/src/test/shortCircuit/short_circuit
output=/src/test/shortCircuit/simdata.txt
INPUTS="
/src/test/shortCircuit/input/C/sin_C_10.net
...
"

echo -e "\n\n🚀 Start tesing performance about capcitor"
free -h
echo -e "\n"

for file in $INPUTS; do
	echo "Processing $file"
	for i in 1 2 3 4 5; do
		{ time $short_circuit $file >$output 2> /dev/null; } |& grep real

		sleep 2
	done
	echo -e "\n\n"
done
```

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_RCL_comparisondlF6v7.png" alt="performance_RCL_comparison" style="zoom: 40%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_inductorrtr6Nx.png" alt="performance_inductor" style="zoom: 40%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_linear_refRRVnmq.png" alt="performance_linear_ref" style="zoom: 40%;" />

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_resistor93b0zi.png" alt="performance_resistor" style="zoom:40%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_capacitor6xBjdd.png" alt="performance_capacitor" style="zoom:40%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_exp_ref7M9eak.png" alt="performance_exp_ref" style="zoom:40%;" />

By comparing to the reference of linear and exponential growth, it is clear to see that the execution time required to solving a circuit mostly composited of inductors or capacitors increases linearly with number of inductors or capacitor. In contrast, the execution time required to solving a circuit mostly composited of resistor grows exponentially with the number of resistors in it. The key to explain this difference in time complexity lies in the algorithm and the way how test circuits are built. In order to overcome the lack of impedance in capacitor and inductor model, test circuits for inductor use more parallel connection but test circuits for capacitor use more serial connection which introduce more nodes and therefore more rows in the MNA matrixes. It is not quite sure about the exact complexity of the inversion algorithm used in Eigen, but a common one should be around O(n^3), see [inversion complexity]. In addition, though capacitor has a relative linear complexity, it requires significant more time to compute the amount of components comparing to Resistor. This is because capacitor is treated as voltage source in our model and every voltage source needs one extra row and column in the MNA matrix. 

#### Space Complexity







### Data

#### Capacitor

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input `netlist` files [https://github.com/Ouikujie/shortCircuit/tree/master/input/C]

| **#Component** | 10     | 20     | 40     | 80    | 160     | 320     | 640      |
| -------------- | ------ | ------ | ------ | ----- | ------- | ------- | -------- |
| **Round1**     | 0.336  | 0.408  | 0.583  | 2.104 | 11.965  | 73.407  | 548.716  |
| **Round2**     | 0.419  | 0.311  | 0.551  | 2.119 | 11.564  | 74.587  | 554.645  |
| **Round3**     | 0.530  | 0.362  | 0.586  | 2.079 | 11.622  | 73.497  | 551.166  |
| **Round4**     | 0.233  | 0.312  | 0.640  | 2.143 | 11.653  | 73.661  | 552.824  |
| **Round5**     | 0.301  | 0.319  | 0.682  | 2.225 | 11.619  | 73.496  | 550.373  |
| **Average**    | 0.3638 | 0.3424 | 0.6084 | 2.134 | 11.6846 | 73.7296 | 551.5448 |

#### Inductor 

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input netlist files [https://github.com/Ouikujie/shortCircuit/tree/master/input/L]

| **#Component** | 10    | 20    | 40    | 80    | 160   | 320    | 640    |
| -------------- | ----- | ----- | ----- | ----- | ----- | ------ | ------ |
| **Round1**     | 0.306 | 0.353 | 0.287 | 0.392 | 0.405 | 0.853  | 1.428  |
| **Round2**     | 0.299 | 0.308 | 0.308 | 0.301 | 0.358 | 0.908  | 1.420  |
| **Round3**     | 0.317 | 0.254 | 0.352 | 0.342 | 0.453 | 0.957  | 1.336  |
| **Round4**     | 0.239 | 0.304 | 0.344 | 0.331 | 0.440 | 0.915  | 1.407  |
| **Round5**     | 0.274 | 0.336 | 0.284 | 0.294 | 0.414 | 0.828  | 1.597  |
| **Average**    | 0.287 | 0.311 | 0.315 | 0.332 | 0.414 | 0.8922 | 1.4376 |

#### Resistor 

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input netlist files [https://github.com/Ouikujie/shortCircuit/tree/master/input/R]

| **#Component** | 10    | 20     | 40     | 80     | 160    | 320    | 640     |
| -------------- | ----- | ------ | ------ | ------ | ------ | ------ | ------- |
| **Round1**     | 0.323 | 0.300  | 0.448  | 0.712  | 0.986  | 1.879  | 76.272  |
| **Round2**     | 0.298 | 0.301  | 0.375  | 0.653  | 0.938  | 1.987  | 76.138  |
| **Round3**     | 0.305 | 0.380  | 0.350  | 0.661  | 0.864  | 1.833  | 75.855  |
| **Round4**     | 0.279 | 0.382  | 0.284  | 0.657  | 0.941  | 1.931  | 76.394  |
| **Round5**     | 0.230 | 0.385  | 0.376  | 0.693  | 0.949  | 1.979  | 75.883  |
| **Average**    | 0.287 | 0.3496 | 0.3666 | 0.6752 | 0.9356 | 1.9218 | 76.1084 |



[repo] https://github.com/Ouikujie/shortCircuit/

[inversion complexity] https://en.wikipedia.org/wiki/Computational_complexity_of_mathematical_operations#Matrix_algebra

[executable file] https://github.com/Ouikujie/shortCircuit/blob/master/test/performance/sample_result/short_circuit


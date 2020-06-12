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
├── CMakeLists.txt.gtest
├── README.md
├── extern
│   ├── Eigen
│   └── spdlog
├── include
│   ├── circuit.hpp
│   ├── component.hpp
│   ├── linear_components.hpp
│   ├── node.hpp
│   ├── nonlinear_components.hpp
│   └── parser.hpp
├── input/ # contain various netlist files
├── main.cpp
├── makefile
├── short_circuit
├── src
│   ├── circuit.cpp
│   ├── component.cpp
│   ├── linear_components.cpp
│   ├── node.cpp
│   ├── nonlinear_components.cpp
│   └── parser.cpp
└── test
    ├── performance
    ├── test_capacitor.cpp
    ├── test_circuit.cpp
    ├── test_inductor.cpp
    ├── test_node.cpp
    ├── test_parser.cpp
    └── test_resistor.cpp
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

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_current_refsPTeo6.png" alt="CLR_simulation_current_ref" style="zoom: 33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_current_LUXmNLzF.png" alt="CLR_simulation_current_LU" style="zoom: 33%;" />

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_voltage_refjMTaPW.png" alt="CLR_simulation_voltage_ref" style="zoom: 33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_voltage_LUY8eEX0.png" alt="CLR_simulation_voltage_LU" style="zoom: 33%;" />

Numeric analysis was suggested at the first place during group discussion but the viable time step solver feature of LTSpice causing the reference data set to have a different size than the target one and therefore make direct comparison of the Euclidean distance impossible. Graphical comparison was then proposed and used.

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/comparison_I%28L1%293eyroZ.png" alt="comparison_I(L1)" style="zoom: 33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/comparison_VN0025N8JQs.png" alt="comparison_VN002" style="zoom: 33%;" />

As the figures show, the main deviation occurs at the start of the simulation. This might due to a different assumption about the initial condition of the circuit. In our model of component, inductor is treated as open circuit when start operating and capacitor is treated as short circuit when start operating. Thus current of inductor starts zero.

![CLR_simulation_comparison](https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/CLR_simulation_comparisonkIOpCE.png)

By comparing the minimum and maximum values with reference after the first second, it is confident to confirm that these two data sets are similar with only 1.1% error in maximum. 

#### Time Complexity

Two groups of tests were carried to investigate the time complexity of our program. 

In the first group, every `netlist` file contains a various of supported component model to mimic a real life situation and different numbers of nodes. The following graph is plotted with time to solve against number of nodes. Logarithmic scale are applied on both axises since data points scatter in large range. By comparing to exponential growth, the time consumption of our program tends to increase much slower than exponential growth but still faster than logarithmic or linear growth. Since the fastest algorithm to do LU decomposition has complexity around O(n^2.75) [LU complexity], this result reaches our goal to high efficiency. 

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/time_consumption_related_to_node_numberOAFcRf.png" alt="time_consumption_related_to_node_number" style="zoom:50%;" />

The second group involving a series of tests that were conducted with different numbers of a single type of components in each test. This group of test is designed to investigate the difference in time complexity for each type of component. By comparing to the reference of linear and exponential growth, it is clear to see that the execution time required to solving a circuit mostly composited of inductors or capacitors increases linearly with number of inductors or capacitor. In contrast, the execution time required to solving a circuit mostly composited of resistor grows exponentially with the number of resistors in it. The key to explain this difference in time complexity lies in the algorithm and the way how test circuits are built. In order to overcome the lack of impedance in capacitor and inductor model, test circuits for inductor use more parallel connection but test circuits for capacitor use more serial connection which introduce more nodes and therefore more rows in the MNA matrixes. In addition to the trend, although time consumption of capacitor increases relatively slower than resistor, it requires significant more time to compute the same amount of components. This is because capacitor is treated as voltage source in our model and every voltage source needs one extra row and column in the MNA matrix. 

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/RCL_comparison_LUzSjF0O.png" alt="RCL_comparison_LU" style="zoom:33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/capacitor_LU84zUeB.png" alt="capacitor_LU" style="zoom:33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/inductor_LUMZOFTi.png" alt="inductor_LU" style="zoom:33%;" />

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/resistor_LU4TsOgA.png" alt="resistor_LU" style="zoom:33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_linear_refRRVnmq.png" alt="performance_linear_ref" style="zoom: 33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/performance_exp_ref7M9eak.png" alt="performance_exp_ref" style="zoom: 33%;" />

All these tests are conducted using the same executable file and the same docker container running on Arch Linux with 2.5 gigabytes free memory and 4 CPU cores. In order to minimise the potential turbulence caused by background processes and core temperature, etc, each input file was tested for five time to find the average execution time. 

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



#### Different methods to solve matrix

The Eigen linear algebra library used in our project supports several methods to solve linear system [methods to solve matrix]. Two methods have been investigated by our group in this project, solving by taking inverse of A  and solving by using LU decomposition.

```c++
_x = _A.inverse()*_b		// solve by taking inverse of A
_x = _A.lu().solve(_b);	// solve by using LU decomposition
```

##### Time complexity

Time complexity of the use of the two methods does not show significant improvement from one to another.

<img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/RCL_comparison_LU3Fy5z8.png" alt="RCL_comparison_LU" style="zoom: 33%;" /><img src="https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/time_consumption_inversemAp7EG.png" alt="time_consumption_inverse" style="zoom:33%;" />

##### Execution speed

For small size matrix(smaller than 100 rows and columns), these two methods result in similar execution speed. But as the node size increases, LU decomposition out performs inversion and saving about 2/3 of execution time which is impressive. 



## Data

### Execution time

#### Capacitor

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input `netlist` files [https://github.com/Ouikujie/shortCircuit/tree/master/input/C]

![capacitor](https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/capacitorPRR319.png)

#### Inductor 

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input netlist files [https://github.com/Ouikujie/shortCircuit/tree/master/input/L]

![inductor](https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/inductorQLUkoV.png)

#### Resistor 

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input netlist files [https://github.com/Ouikujie/shortCircuit/tree/master/input/R]

![resistor](https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/resistorYtygPY.png)

#### Node

Generated by docker container running on Arch linux with 4 CPU cores and 2.5 gigabytes free memory

Input netlist files [https://github.com/Ouikujie/shortCircuit/tree/master/input/node]

![node](https://cdn.jsdelivr.net/gh/ouikujie/image@master/Mac/nodeDMPItH.png)

[repo] https://github.com/Ouikujie/shortCircuit/

[inversion complexity] https://en.wikipedia.org/wiki/Computational_complexity_of_mathematical_operations#Matrix_algebra

[executable file] https://github.com/Ouikujie/shortCircuit/blob/master/test/performance/sample_result/short_circuit

[methods to solve matrix] https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html

[LU complexity] https://en.wikipedia.org/wiki/Coppersmith%E2%80%93Winograd_algorithm
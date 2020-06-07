#!/bin/bash
set -e

short_circuit=/src/test/shortCircuit/short_circuit
output=/src/test/shortCircuit/simdata.txt
INPUTS="
/src/test/shortCircuit/input/C/sin_C_10.net
/src/test/shortCircuit/input/C/sin_C_20.net
/src/test/shortCircuit/input/C/sin_C_40.net
/src/test/shortCircuit/input/C/sin_C_80.net
/src/test/shortCircuit/input/C/sin_C_160.net
/src/test/shortCircuit/input/C/sin_C_320.net
/src/test/shortCircuit/input/C/sin_C_640.net
"

echo -e "\n\n🚀 Start tesing performance about capcitor"
#free -h | grep Mem | awk '{print available Mem $4}'
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

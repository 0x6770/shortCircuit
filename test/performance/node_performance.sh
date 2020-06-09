#!/bin/bash
set -e

short_circuit=/src/test/shortCircuit/short_circuit
output=/src/test/shortCircuit/simdata.txt
INPUTS="
/src/test/shortCircuit/input/node/nodes_10.net
/src/test/shortCircuit/input/node/nodes_31.net
/src/test/shortCircuit/input/node/nodes_64.net
/src/test/shortCircuit/input/node/nodes_131.net
/src/test/shortCircuit/input/node/nodes_196.net
/src/test/shortCircuit/input/node/nodes_329.net
/src/test/shortCircuit/input/node/nodes_460.net
/src/test/shortCircuit/input/node/nodes_592.net
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

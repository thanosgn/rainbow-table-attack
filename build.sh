#!/bin/bash

for i in $(seq 1 $1);
do
	./build_rainbow_table $i &
done

wait
echo "Done building"
#!/bin/sh

for i in `seq 1 $1`;
do
	./rainbow_attack $i &
done
wait
#!/bin/bash
HASH_FILE='/home/thanos/repositories/rainbow-attack/hash_file.txt'
touch ${HASH_FILE}
for i in `seq 1 $1`;
do
	./rainbow_attack $i < ${HASH_FILE} &
done
while true
do
	echo "Type Hash:"
	read hash
	echo "$hash" >> ${HASH_FILE} 
done
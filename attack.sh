#!/bin/bash


# for i in `seq 1 $1`;
# do
# 	./rainbow_attack $i &
# done
# wait

HASH_FILE='/home/thanos/repositories/rainbow-attack/hash_file.txt'
for i in `seq 1 $1`;
do
	./rainbow_attack $i < ${HASH_FILE} &
done
while true
do
	echo "Type Hash:"
	read hash
	echo "$hash" >> ${HASH_FILE} 

	# wait
done
# wait
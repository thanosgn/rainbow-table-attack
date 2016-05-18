#!/bin/sh


for i in `seq 1 $1`;
do
	./rainbow_attack $i &
done
wait

# #!/bin/sh

# while true
# do
# 	echo "Type Hash:"
# 	read hash

# 	for i in `seq 1 $1`;
# 	do
# 		./rainbow_attack $i $hash &
# 	done
# 	# wait
# done
# # wait
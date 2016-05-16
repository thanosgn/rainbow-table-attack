#
# In order to execute this "Makefile" just type "make"
#

OBJSBUILD 	= rainbow_table_builder.o blake256.o base64.o rainbow_table.o MurmurHash3.o
OBJSATTACK 	= rainbow_attack.o rainbow_table.o blake256.o base64.o MurmurHash3.o
SOURCEBUILD	= rainbow_table_builder.cpp blake256.cpp base64.cpp rainbow_table.cpp MurmurHash3.cpp
SOURCEATTACK	= rainbow_attack.cpp rainbow_table.cpp blake256.cpp base64.cpp MurmurHash3.cpp
HEADER  = blake.h rainbow_table.hpp MurmurHash3.h
OUTBUILD  	= build_rainbow_table
OUTATTACK  	= rainbow_attack
CC		= g++
FLAGS 	= -c -g -O2 -std=c++11
LFLAGS 	= -L/gmp_install/lib -lgmp -lpthread -lm -lssl -lcrypto
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: BUILD ATTACK

BUILD: $(OBJSBUILD)
	$(CC) $(OBJSBUILD) $(LFLAGS) -o $(OUTBUILD)


ATTACK: $(OBJSATTACK)
	$(CC) $(OBJSATTACK) $(LFLAGS) -o $(OUTATTACK)

# create/compile the individual files >>separately<< 
rainbow_table.o: rainbow_table.cpp rainbow_table.hpp
	$(CC) $(FLAGS) rainbow_table.cpp

rainbow_table_builder.o: rainbow_table_builder.cpp rainbow_table.hpp
	$(CC) $(FLAGS) rainbow_table_builder.cpp

rainbow_attack.o: rainbow_attack.cpp rainbow_table.hpp
	$(CC) $(FLAGS) rainbow_attack.cpp

blake256.o: blake256.cpp blake.h
	$(CC) $(FLAGS) blake256.cpp

base64.o: base64.cpp base64.h
	$(CC) $(FLAGS) base64.cpp

# hextobase64.o: hextobase64.cpp
# 	$(CC) $(FLAGS) hextobase64.cpp

# clean house
clean:
	rm -f $(OUTBUILD) $(OBJSATTACK) $(OUT)

clena:
	rm -f $(OUTBUILD) $(OBJSATTACK) $(OUT)

claen:
	rm -f $(OUTBUILD) $(OBJSATTACK) $(OUT)


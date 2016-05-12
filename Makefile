#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= rainbow_table_builder.o blake256.o base64.o
SOURCE	= rainbow_table_builder.cpp blake256.cpp base64.cpp
HEADER  = blake.h
OUT  	= build_rainbow_table
CC		= g++
FLAGS 	= -c -g -Wno-write-strings -O2
LFLAGS 	= -L/gmp_install/lib -lgmp -lpthread -lm -lssl -lcrypto
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT)

# create/compile the individual files >>separately<< 
rainbow_table_builder.o: rainbow_table_builder.cpp blake.h
	$(CC) $(FLAGS) rainbow_table_builder.cpp

blake256.o: blake256.cpp blake.h
	$(CC) $(FLAGS) blake256.cpp

base64.o: base64.cpp
	$(CC) $(FLAGS) base64.cpp

# hextobase64.o: hextobase64.cpp
# 	$(CC) $(FLAGS) hextobase64.cpp

# clean house
clean:
	rm -f $(OBJS) $(OUT)

clena:
	rm -f $(OBJS) $(OUT)

claen:
	rm -f $(OBJS) $(OUT)


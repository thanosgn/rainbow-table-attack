#include <iostream>
#include <openssl/sha.h>
#include "blake.h"
#include "base64.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_OF_CHAINS 1024
#define CHAIN_LENGTH 1024




void build_chain(int);
char* random_pass();
void base_64(unsigned char*, char*);
char* reduce(char*, uint8_t* , int);
void print_uint8_t(uint8_t*);
void print_hash(uint8_t*, int);
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
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
#include <string>
#include <pthread.h>
#define NUM_OF_CHAINS 5000
#define CHAIN_LENGTH 5000

using namespace std;



void build_chain(int);
char* random_pass();
void base_64(unsigned char*, char*);
char* reduce(char*, uint8_t* , int);
void print_uint8_t(uint8_t*);
void print_hash(uint8_t*, int);
void fprint_hash(uint8_t*, int);
bool searchHash(map<string, string>, string);
void findPass(map<string, string>, string, string);
void transform_uint8_t_array_to_string(uint8_t*, string&);
void transform_string_to_uint8_t_array(uint8_t*, string&);
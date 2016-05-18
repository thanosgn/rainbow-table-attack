#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <openssl/sha.h>
#include "blake.h"
#include "base64.h"
#include "MurmurHash3.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
#define NUM_OF_CHAINS 5000000
#define CHAIN_LENGTH 1000
#define BLOCK256 64

using namespace std;



void build_chain(int,FILE*);
char* random_pass();
void base_64(unsigned char*, char*);
char* reduce(char*, uint8_t* , int);
void print_uint8_t(uint8_t*);
void print_hash(uint8_t*, int);
void fprint_hash(uint8_t*, int, FILE*);
bool searchHash(unordered_map<string, string>, string);
bool findPass(unordered_map<string, string>, string, string);
void transform_uint8_t_array_to_string(uint8_t*, string&);
void transform_string_to_uint8_t_array(uint8_t*, string&);
uint8_t* hash_function(uint8_t*, char*);
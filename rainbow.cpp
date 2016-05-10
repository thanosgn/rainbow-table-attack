#include <iostream>
#include <openssl/sha.h>
#include "blake.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define NUM_OF_CHAINS 1024
#define CHAIN_LENGTH 5000

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";

char* random_pass(){
	char* pass = new char[7];
	int i = 0;
	for(i=0; i<7; i++){
		pass[i] = base64_table[rand()%64];
	}
	pass[6]='\0';
	return pass;
}

int Base64Encode(const char* message, char** buffer) { //Encodes a string to base64
  BIO *bio, *b64;
  FILE* stream;
  // int encodedSize = 4*ceil((double)strlen(message)/3);
  int encodedSize = 6;
  // *buffer = (char *)malloc(encodedSize+1);

  stream = fmemopen(*buffer, encodedSize+1, "w");
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_fp(stream, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
  BIO_write(bio, message, strlen(message));
  BIO_flush(bio);
  BIO_free_all(bio);
  fclose(stream);
 //  int i = 0;
	// while(*buffer[i] != '\0'){
	// 	if(*buffer[i] == '+' || *buffer[i] == '=')
	// 		*buffer[i] = '!';
	// 	if(*buffer[i] == '/')
	// 		*buffer[i] = '@';
	// 	i++;
	// 	}
	// 	if(strlen(*buffer) < 6){
	// 	while(i<6){
	// 		// *buffer[i]='a';
	// 		*buffer[i]=base64_table[i];
	// 		i++;
	// 	}
	// }
	return (0); //success
}

void base_64(unsigned char* hash, char* base64){
	Base64Encode((char*)hash, &base64);
	int i = 0;
	while(base64[i] != '\0'){
		if(base64[i] == '+' || base64[i] == '=')
			base64[i] = '!';
		if(base64[i] == '/')
			base64[i] = '@';
		i++;
	}
	if(strlen(base64) < 6){
		while(i<6){
			// base64[i]='a';
			base64[i]=base64_table[i];
			i++;
		}
	}
}

char* reduce(char *base64, uint8_t* hashed){
	const unsigned char* data = (const unsigned char*)hashed;
	size_t length = sizeof(data);
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1(data, length, hash);
	base_64(hash, base64);
	base64[6]='\0';
	return base64;
}

void build_chain(int chain_length){
	char* first_pass = random_pass();
	uint8_t* out = new uint8_t[32];
	char *base64 = new char[7];
	int i = 0;
	printf("%s\t",first_pass);
	char* str = first_pass;
	while(i<chain_length){
		// printf("%s\n",str );
		out = hash(out, str);
		// print_hash(out);
		base64 = reduce(base64, out);
		str = base64;
		i++;
	}
	printf("%s\n",base64);
	// delete[] first_pass;
	delete[] out;
	delete[] base64;
}



int main( int argc, char **argv ){
	srand(time(NULL));
	int i;
	for (i = 0; i < NUM_OF_CHAINS; ++i)
	{
		build_chain(CHAIN_LENGTH);
	}
	return 0;
}

void print_hash(uint8_t* hash){
	int j;
	for( j = 0; j < 32; ++j )
		printf( "%02x", hash[j] );
}

// char* sprint_hash(uint8_t* hash){
// 	char* str = (char*)malloc(65*sizeof(char));
// 	int j;
// 	for( j = 0; j < 32; ++j )
// 		sprintf(str,"%02x", hash[j] );
// 	return str;
// }
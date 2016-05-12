#include "rainbow_table.hpp"
using namespace std;
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";

void build_chain(int chain_length){
	char* first_pass = random_pass();
	uint8_t* out = new uint8_t[32];
	char *base64 = new char[7];
	int i = 0;
	printf("%s\t",first_pass);
	char* str = first_pass;
	while(i<chain_length){
		out = hash(out, str);
		base64 = reduce(base64, out, i);
		str = base64;
		i++;
	}
	out = hash(out, str);
	print_hash(out,32);
	delete[] first_pass;
	delete[] out;
	delete[] base64;
}

char* random_pass(){
	char* pass = new char[7];
	int i = 0;
	for(i=0; i<7; i++){
		pass[i] = base64_table[rand()%64];
	}
	pass[6]='\0';
	return pass;
}


void base_64(unsigned char* hash, char* base64){
	const char* const_hash = reinterpret_cast<const char *>( hash);
	Base64encode(base64, const_hash, 6);
}

char* reduce(char *base64, uint8_t* hashed, int round){
	const unsigned char* data = (const unsigned char*)hashed;

	char new_data[50];
	memset(new_data, '\0', 50);
	memcpy(new_data, data, 32);
	int index = 32;
	while (round > 0){
		int digit = round%10;
		new_data[index]=digit;
		round /= 10;
		index++;
	}

	size_t length = sizeof(new_data);
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1((const unsigned char*)new_data, length, hash);
	base_64(hash, base64);
	base64[6]='\0';
	return base64;
}



void print_uint8_t(uint8_t* hash){
	int j;
	for( j = 0; j < 32; ++j )
		cout << unsigned(hash[j]) << " ";
	cout << endl;	
}

void print_hash(uint8_t* hash, int length){
	int j;
	for( j = 0; j < length; ++j )
		printf( "%02x", hash[j] );
	printf("\n");
}
#include "rainbow_table.hpp"
using namespace std;
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


void base_64(unsigned char* hash, char* base64){
	const char* const_hash = reinterpret_cast<const char *>( hash);
	Base64encode(base64, const_hash, 6);
}


uint8_t* hash_function(uint8_t* out, char* str) {
#define BLOCK256 64
  // uint8_t* out = new uint8_t[32];
  blake256_hash(out, (uint8_t*)str, strlen(str));
  return out;
}

char* reduce(char *base64, uint8_t* hashed, int round){
	// const unsigned char* data = (const unsigned char*)hashed;

	// char new_data[50];
	// memset(new_data, '\0', 50);
	// memcpy(new_data, data, 32);
	// int index = 32;
	// while (round > 0){
	// 	int digit = round%10;
	// 	new_data[index]=digit;
	// 	round /= 10;
	// 	index++;
	// }

	// size_t length = sizeof(new_data);
	// unsigned char hash[SHA_DIGEST_LENGTH];
	// SHA1((const unsigned char*)new_data, length, hash);
	

	// printf("Hash: ");
	// print_hash(hashed,32);
	
	uint8_t hash[16];
	MurmurHash3_x64_128(hashed, 32, round, hash);
	
	// printf("(%d)MurMur: \n",round);
	// print_hash((uint8_t*)hash,16);


	base_64((unsigned char*)hash, base64);
	// printf("Base64: %s\n",base64);
	base64[6]='\0';
	// printf("Base64: %s\n",base64);
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

void fprint_hash(uint8_t* hash, int length, FILE* fd){
	int j;
	for( j = 0; j < length; ++j )
		fprintf(fd, "%02x", hash[j] );
	fprintf(fd, "\n");
}

void build_chain(int chain_length, FILE* fd){
	char* first_pass = random_pass();
	uint8_t* out = new uint8_t[32];
	char *base64 = new char[7];
	int i = 0;
	fprintf(fd, "%s\t",first_pass);
	// printf("%s\n",first_pass);
	char* str = first_pass;
	while(i<chain_length-1){
		out = hash_function(out, str);
		// fprintf(stderr, "hash: \n");
		// fprint_hash(out,32);
		base64 = reduce(base64, out, i);
		// printf("%s\n",base64 );
		str = base64;
		i++;
	}
	out = hash_function(out, str);
	fprint_hash(out,32,fd);
	// print_hash(out,32);
	delete[] first_pass;
	delete[] out;
	delete[] base64;
}

bool findPass(unordered_map<string, string> hashMap, string chain_start, string hash1){
	bool found = false;
	uint8_t* out = new uint8_t[32];
	char *base64 = new char[7];
	strcpy(base64,&chain_start[0]);
	string hash2(hash1);
	int i = 0;
	// cout << "FindPass for " << hash1 << " Start: " << chain_start << endl;
	while(!found && i < CHAIN_LENGTH){
		out = hash_function(out, base64);
		transform_uint8_t_array_to_string(out,hash2);
		if(hash1.compare(hash2) == 0){
			found = true;
			cout << "Found solution for " << hash1 << "! Pass: " << base64 << endl;
			return true;
		}
		base64 = reduce(base64, out, i);
		i++;
	}
	return false;
}

void transform_string_to_uint8_t_array(uint8_t* out, string& hash){
	for (int i = 0; i < hash.size(); i+=2){
		int result = 0;
		char c1 = hash[i];
		char c2 = hash[i+1];
		result += (isdigit(c1)) ? (c1-'0')*16 : (c1-'a'+10)*16;
		result += (isdigit(c2)) ? (c2-'0') : (c2-'a'+10);
		out[i/2] = result;
		// cout << "Char1: " <<  c1 << " Char2: " << c2 << " Result: " << result << " out[i/2] " << unsigned(out[i/2]) << endl ;
	}	
	// return out;
}

void transform_uint8_t_array_to_string(uint8_t* array, string& hash){
	for (int i = 0, j = 0; i < 32; i++, j+=2){
		int num = array[i];
		int modulo = num%16;
		int quotient = num/16;
		hash[j] = (quotient > 9) ? ('a'+quotient-10) : quotient + '0'; 
		hash[j+1] = (modulo > 9) ? ('a'+modulo-10) : modulo + '0'; 
	}
	// return hash;
}

bool searchHash(unordered_map<string, string> hashMap, string hash1){
	int i = CHAIN_LENGTH-2;
	bool found = false;
	string chain_start;
	string original_hash (hash1);
	unordered_map<string, string>::iterator it;
	char *base64 = new char[7];
	uint8_t* out = new uint8_t[32];
	while(!found && i >= -1){
		if((it = hashMap.find(hash1)) != hashMap.end()){
			chain_start = it->second;
			if (findPass(hashMap, chain_start, original_hash) == true){
				return true;
			} else {
				hash1 = original_hash;
				//Reduce-Hash CHAIN_LENGTH-1-i times
				transform_string_to_uint8_t_array(out, hash1);
				for (int j = 0; j < CHAIN_LENGTH-i-1; j++){
					// printf("To be reduced: ");
					// print_hash(out,32);
					base64 = reduce(base64, out, i+j);
					// printf("(%d)Reduced: %s\n",i+j,base64 );
					//Hash
					out = hash_function(out, base64);
					// printf("Hashed: ");
					// print_hash(out,32);
				}
				// printf("End for loop\n");
				transform_uint8_t_array_to_string(out, hash1);
				// cout << "String: " << hash1 << endl;
				i--;
			}
		} else {
			// printf("Round: %d\n",i );
			hash1 = original_hash;
			//Reduce-Hash CHAIN_LENGTH-1-i times
			transform_string_to_uint8_t_array(out, hash1);
			for (int j = 0; j < CHAIN_LENGTH-i-1; j++){
				// printf("To be reduced: ");
				// print_hash(out,32);
				base64 = reduce(base64, out, i+j);
				// printf("(%d)Reduced: %s\n",i+j,base64 );
				//Hash
				out = hash_function(out, base64);
				// printf("Hashed: ");
				// print_hash(out,32);
			}
			// printf("End for loop\n");
			transform_uint8_t_array_to_string(out, hash1);
			// cout << "String: " << hash1 << endl;
			i--;
		}
	}
	delete[] out;
	delete[] base64;
	return found;
}
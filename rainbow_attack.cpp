#include "rainbow_table.hpp"


using namespace std;
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";


int main (int argc, char* argv[]){
	int table_number = atoi(argv[1]);
	char rainbow_table[50];
	sprintf(rainbow_table, "table%d.csv", table_number);
	ifstream file(rainbow_table);
	int i;
	string pass, hash;
	unordered_map<string, string> hashMap;
	while(!file.eof()){
		file >> pass;
		file >> hash;
		hashMap.insert(pair<string, string>(hash,pass));
	}
	char hash_filename[50] = "hashes.txt";
	string hash1, hash2, line;
	ifstream hash_file(hash_filename);
	while(!hash_file.eof()){
		hash_file >> hash2;
		cout << "Searching: " << hash2 << " in table " << table_number << endl;
		searchHash(hashMap, hash2);
		if(searchHash(hashMap, hash2) == true)
			break;
	}
	// char* out = new char[16];
	// MurmurHash3_x64_128 ( "lalala", strlen("lalala"), 0, out );
	// // cout << "out: " << out << endl;
	// print_hash((uint8_t*)out, 16);
	// char* base64 = new char[7];
	// base_64((unsigned char *)out,base64);
	// base64[6]='\0';
	// cout << "base64: " << base64;
	return 0;
}


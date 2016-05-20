#include "rainbow_table.hpp"
#include <fstream>
#include <unistd.h>

using namespace std;
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";


int main (int argc, char* argv[]){
	char rainbow_table[50];
	int table_number = atoi(argv[1]);
	sprintf(rainbow_table, "table%d.csv", table_number);
	ifstream file(rainbow_table);
	string pass, hash;
	unordered_map<string, string> hashMap;
	while(!file.eof()){	//Build Map
		file >> pass;
		file >> hash;
		hashMap.insert(pair<string, string>(hash,pass));
	}
	char str[65];
	while(true){ //Wait for input
		if((cin.getline(str,65))){
			string hash2(str);
			searchHash(hashMap, hash2);
		} else {
			usleep(500000);
			cin.clear();
		}
	}
	return 0;
}


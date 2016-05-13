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
	map<string, string> hashMap;
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
		if(searchHash(hashMap, hash2) == true)
			break;
	}
	// while(std::getline(hash_file, line)){
	//     stringstream linestream(line);
	//     string data;
	//     getline(linestream, data, ':');
	//     linestream >> hash1;
	//     cout << hash1;
	// }
	return 0;
}
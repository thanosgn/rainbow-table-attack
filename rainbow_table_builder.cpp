#include "rainbow_table.hpp"

using namespace std;
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";


int main(int argc, char **argv){
	srand(getpid());
	int table_number = atoi(argv[1]);
	int i;
	for (i = 0; i < NUM_OF_CHAINS; ++i){
		build_chain(CHAIN_LENGTH);
	}
	return 0;
}

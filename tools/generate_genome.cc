#include <iostream.h>
#include <string>
#include <stdlib.h>
#include <map>

using namespace std;

char A[] = "ACTG";

ostream &rand_nucleotid(ostream &os) {
	int i = rand()%(sizeof(A)-1);
	return os << A[i];
}

int rand_sequence(ostream &os, int size) {
	while (size-- > 0) rand_nucleotid(os);
	return size;
}

int main(int argc, char *argv[]) {
	int size = (argc > 1)? atoi(argv[1]): 10000;

	rand_sequence(cout, size);

	return 0;
}

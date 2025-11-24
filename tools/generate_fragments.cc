#include <iostream>
#include <string>

using namespace std;

int read(ostream &os, const string &str, int fragmin, int fragmax) {
	int start = rand() % str.size();
	int len = fragmin + (rand() % (fragmax - fragmin));
	if (start + len > str.size()) len = str.size() - start;

	os << string(str, start, len);

	return len;
}

int main(int argc, char *argv[]) {
	string line;
	cin >> line;

	int coverage = (argc > 1)? atoi(argv[1]): 10;
	int fmin = (argc > 2)? atoi(argv[2]): 600;
	int fmax = (argc > 3)? atoi(argv[3]): fmin + 100;
	int len = line.size();
	int r = 0;

	while(r < len * coverage) {
		cout << ".";
		r += read(cout, line, fmin, fmax);
		cout << "." << endl;
	}
}


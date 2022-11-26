#include <iostream>

using namespace std;

int test(int& a) {
	a += 42;
}

int main() {
	int truc(10.0);

	int machin = test(truc);

	cout << machin << endl;

	return 0;
}
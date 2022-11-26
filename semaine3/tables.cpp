#include <iostream>

using namespace std;

int main() {
	cout << "Tables de multiplication" << endl;

	for (int i(2); i <= 10; ++i) {
		cout << "Table de " << i << " :" << endl;
		for (int j(1); j <= 10; ++j) {
			cout << j << " * " << i << " = " << j*i << endl;

		}
	}
    return 0;
}

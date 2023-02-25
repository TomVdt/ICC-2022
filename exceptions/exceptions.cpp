#include <iostream>
#include <string>

using namespace std;

enum Excpetion {
    DIVZERO,
};

double f(double x) {
    if (x == 0.0) {
        throw DIVZERO;
    }
    return 1 / x;
}

int main() {
	double y(0);
    try {
        y = f(1);
		cout << "f(" << 1 << ") = " << y << endl;
    }
	catch (Excpetion e) {
		cerr << "Error " << e << endl;
    }

    return 0;
}
#include <cmath>
#include <iostream>

using namespace std;

double factorielle(int k) {
    double fac(1);
    for (int i(2); i <= k; ++i) {
        fac *= i;
    }
    return fac;
}

double somme_partielle(double x, int N) {
    double y(0);
    for (int i(0); i <= N; ++i) {
        y += pow(-1, i) * pow(x, 2 * i) / factorielle(2 * i);
    }
    return y;
}

int main() {
    int N;
    do {
        cout << "Nombre N: ";
        cin >> N;
    } while (N < 1);

    double x;
    do {
        cout << "Nombre x: ";
        cin >> x;
    } while (x < 0.0 or x > 2 * M_PI);

    cout.precision(12);
    cout << "cos(" << x << ") = " << somme_partielle(x, N) << endl;
	cout << "vrai cos: " << cos(x) << endl;

    return 0;
}

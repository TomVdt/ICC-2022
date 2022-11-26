#include <iostream>
#include <cmath>

using namespace std;

int main() {
	const double g(9.81);

	double H0, eps, h_fin;
	int nbr(0);

	cout << "Hauteur initiale: ";
	cin >> H0;
	if (H0 <= 0) {
		return -1;
	}
	cout << "Coefficient de rebond: ";
	cin >> eps;
	if (!(0 <= eps && eps < 1)) {
		return -1;
	}
	cout << "Hauteur finale: ";
	cin >> h_fin;
	if (!(0 < h_fin && h_fin < H0)) {
		return -1;
	}

	double v(sqrt(2 * H0 * g));
	double v1;
	double h(H0);
	double h1;

	do {
		v1 = eps * v;
		h1 = v1 * v1 / (2 * g);
		
		v = v1;
		h = h1;
		++nbr;
	} while (h > 2.0);

	cout << nbr << " rebond(s)" << endl;

    return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	const double g(9.81);

	double H0, eps;
	int nbr;

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
	cout << "Nombre de rebonds: ";
	cin >> nbr;
	if (nbr < 0) {
		return -1;
	}

	double v(sqrt(2 * H0 * g));
	double v1;
	double h(H0);
	double h1;

	for (int i(0); i < nbr; ++i) {
		v1 = eps * v;
		h1 = v1 * v1 / (2 * g);
		
		v = v1;
		h = h1;
	}

	cout << "Hauteur de la balle après " << nbr << " rebond(s): " << h << endl;

    return 0;
}

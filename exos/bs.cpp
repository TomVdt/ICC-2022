#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct virg_float {
	int signe;
	int mantisse;
	int exposant;
};

void affiche(virg_float nb) {
	double dec(1.0);
	int mant(nb.mantisse);
	for (int i(5); i > 0; i--) {
		if (mant & 0b1) {
			dec += 1.0 / pow(2, i);
		}
		mant >>= 1;
	}
	cout << (nb.signe == 1 ? "-" : "") << dec << " * 2^" << nb.exposant << " = " << (nb.signe * (-2) + 1) * pow(2, nb.exposant) * dec << endl;
}

int main() {
	affiche({0, 6, 2});

    return 0;
}
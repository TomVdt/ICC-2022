#include <iostream>

using namespace std;

int main() {
	double valeur1(42);
	double valeur2(69);
	double valeur3(420);

	double* choix;

	int nb(0);
	do {
		cout << "Choisir un nombre: ";
		cin >> nb;
	} while (nb < 1 || nb > 3);

	switch (nb) {
		case 1:
			choix = &valeur1;
			break;
		case 2:
			choix = &valeur2;
			break;
		case 3:
			choix = &valeur3;
			break;
	}

	cout << "Vous avez choisi " << *choix << endl;

	return 0;
}
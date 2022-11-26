#include <iostream>
#include <string>

using namespace std;

struct Maison {
	string adresse;
};

struct Personne {
	string nom;
	Maison* maison;
};

void afficher(Personne p) {
	cout << p.nom << " habite " << p.maison->adresse << endl;
}

int main() {
	Maison maison1 = { "42 rue du truc" };
	Maison maison2 = { "69 chemin du machin" };

	Personne p1 = { "John", &maison1 };
	Personne p2 = { "Adam", &maison1 };
	Personne p3 = { "Joe", &maison2 };
	Personne p4 = { "Obama", &maison2 };

	afficher(p1);
	afficher(p2);
	afficher(p3);
	afficher(p4);

	Maison maison3 = { "420 allée de la chose" };
	p2.maison = &maison3;

	cout << "Quelqu'un déménage!" << endl;
	afficher(p2);

	return 0;
}
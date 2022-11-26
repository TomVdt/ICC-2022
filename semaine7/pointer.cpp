#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Personne {
    string nom;
	vector<Personne*> amis = vector<Personne*>(0, nullptr);
};

void afficher_amis(const Personne& prs) {
	for (const auto& ami : prs.amis) {
		cout << ami->nom << " ";
	}
	cout << endl;
}

void ajoute_ami(Personne& prs, Personne& ami) {
	prs.amis.push_back(&ami);
}

bool est_ami(Personne& prs, Personne& autre_prs) {
	for (auto& ami : prs.amis) {
		if (ami == &autre_prs) {
			return true;
		}
	}
	return false;
}

int main() {
	Personne juan({"Juan"});
	Personne rodriguez({"Rodriguez"});
	Personne pedro({"Pedro"});
	Personne miguel({"Miguel"});
	Personne philippe({"Philippe"});

	ajoute_ami(juan, rodriguez);
	ajoute_ami(juan, pedro);
	ajoute_ami(juan, miguel);
	ajoute_ami(juan, philippe);
	ajoute_ami(pedro, miguel);
	ajoute_ami(miguel, philippe);
	ajoute_ami(miguel, pedro);

	cout << est_ami(juan, philippe) << endl;
	cout << est_ami(juan, rodriguez) << endl;
	cout << est_ami(miguel, juan) << endl;
	cout << est_ami(pedro, miguel) << endl;

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int Disque;

constexpr Disque PAS_DE_DISQUE(0);
constexpr size_t N(5);

struct Jeu {
	vector<Disque> A;
	vector<Disque> B;
	vector<Disque> C;
};

void affiche(const Disque& d) {
	if (d == PAS_DE_DISQUE) {
		affiche(' ', N);
		affiche('|');
		affiche(' ', N);
	} else {
		affiche(' ', d - N + 1);
		affiche('#', d + 1);
		affiche(' ', d - N + 1);
	}
}

void affiche(char c, unsigned int n = 1) {
	for (size_t i(0); i < n; i++) {
		cout << c;
	}
}

void affiche(const Jeu& jeu) {


	affiche('#', 2*N+1);
	cout << endl;
}

int main() {

	return 0;
}
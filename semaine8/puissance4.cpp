#include <array>
#include <iostream>

using namespace std;

enum Couleur {
	Rouge,
	Jaune,
	Vide
};

// Grille[0] = ligne du haut
// MAIS ca serrait bien d'utiliser 0, 0 pour le bas gauche...
typedef array<array<Couleur, 7>, 6> Grille;

bool diagonale_haut(const Grille& g, int x, int y, Couleur joueur) {
	y = g.size() - y - 1;
	return g[y - 3][x] == joueur && g[y - 3][x] == g[y - 2][x + 1] && g[y - 2][x + 1] == g[y - 1][x + 2] && g[y - 1][x + 2] == g[y][x + 3];
}

bool diagonale_bas(const Grille& g, int x, int y, Couleur joueur) {
	y = g.size() - y - 1;
	return g[y][x] == joueur && g[y][x] == g[y - 1][x + 1] && g[y - 1][x + 1] == g[y - 2][x + 2] && g[y - 2][x + 2] == g[y - 3][x + 3];
}

bool vertical(const Grille& g, int x, int y, Couleur joueur) {
	return g[y][x] == joueur && g[y][x] == g[y + 1][x] && g[y + 1][x] == g[y + 2][x] && g[y + 2][x] == g[y + 3][x];
}

bool horizontal(const Grille& g, int x, int y, Couleur joueur) {
	return g[y][x] == joueur && g[y][x] == g[y][x + 1] && g[y][x + 1] == g[y][x + 2] && g[y][x + 2] == g[y][x + 3];
}

Couleur gagne(const Grille& grille, Couleur joueur) {
	for (int y(0); y < grille.size() - 3; y++) {
		for (int x(0); x < grille[0].size() - 3; x++) {
			if (
				diagonale_bas(grille, x, y + 3, joueur) ||
				diagonale_haut(grille, x, y, joueur) ||
				vertical(grille, x, y, joueur) ||
				horizontal(grille, x, y, joueur)
			) {
				return joueur;
			}
		}
	}

	return Vide;
}

bool plein(const Grille& g) {
	for (const auto& c : g[0]) {
		if (c == Vide) {
			return false;
		}
	}
	return true;
}

char couleur_vers_symbole(Couleur joueur) {
	switch (joueur) {
		case Rouge: return 'x';
		case Jaune: return 'o';
		case Vide: return ' ';
		default: return ' ';
	}
}

void afficher_grille(const Grille& grille) {
	for (int y(0); y < grille.size(); y++) {
		cout << '|';
		for (int x(0); x < grille[0].size(); x++) {
			cout << couleur_vers_symbole(grille[y][x]);
			cout << '|';
		}
		cout << endl;
	}

	cout << '=';
	for (int i(1); i <= grille[0].size(); i++) {
		cout << i << '=';
	}
	cout << endl;
}

int demander_colonne(Couleur joueur) {
	int i(-1);
	cout << "Quelle colonne? (joueur " << couleur_vers_symbole(joueur) << "): ";
	cin >> i;
	return --i;
}

bool jouer(Grille& grille, int colonne, Couleur joueur) {

	if (!(0 <= colonne and colonne < grille[0].size())) {
		return false;
	}

	if (grille[0][colonne] != Vide) {
		return false;
	}

	// Trouver le premier emplacement vide
	int i(grille.size() - 1);
	while (i < grille.size() && grille[i][colonne] != Vide) {
		i--;
	}

	// Remplacer le premier emplacement vide par le joueur
	grille[i][colonne] = joueur;
	return true;
}

int main() {
	Grille grille = {
		Vide, Vide, Vide, Vide, Vide, Vide, Vide,
		Vide, Vide, Vide, Vide, Vide, Vide, Vide,
		Vide, Vide, Vide, Vide, Vide, Vide, Vide,
		Vide, Vide, Vide, Vide, Vide, Vide, Vide,
		Vide, Vide, Vide, Vide, Vide, Vide, Vide,
		Vide, Vide, Vide, Vide, Vide, Vide, Vide
	};

	bool victoire(false);
	Couleur joueur(Rouge);
	
	afficher_grille(grille);
	while (!victoire and !plein(grille)) {

		int colonne(demander_colonne(joueur));

		bool valide(jouer(grille, colonne, joueur));

		if (valide) {
			victoire = gagne(grille, joueur) == joueur;
			joueur = joueur == Rouge ? Jaune : Rouge;
			afficher_grille(grille);
		}
	}

	if (victoire) {
		afficher_grille(grille);
		cout << "Le joueur " << couleur_vers_symbole(joueur == Rouge ? Jaune : Rouge) << " a gagné!" << endl;
	} else {
		cout << "Égalité!" << endl;
	}

	return 0;
}

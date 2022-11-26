#include <array>
#include <iostream>
#include <vector>

using namespace std;

constexpr unsigned int DIM(10);

bool remplitGrille(array<array<bool, DIM>, DIM>& grille,
                   unsigned int ligne, unsigned int colonne,
                   char direction, unsigned int longueur) {
    int x(colonne), y(ligne);
    vector<pair<int, int>> positions;

    for (int i(0); i < longueur; i++) {
        positions.push_back(pair<int, int>(x, y));
        switch (direction) {
            case 'N':
                y--;
                break;
            case 'S':
                y++;
                break;
            case 'E':
                x++;
                break;
            case 'O':
                x--;
                break;
        }
    }

    bool hit(false);
    for (auto pos : positions) {
        if (grille[pos.second][pos.first]) {
			hit = true;
		}
    }

    if (!hit) {
        for (auto pos : positions) {
            grille[pos.second][pos.first] = true;
        }
    }

    return !hit;
}

void show_field(array<array<bool, DIM>, DIM> grille) {
	for (auto row : grille) {
        for (auto val : row) {
            cout << (val ? '#' : '.');
        }
        cout << endl;
    }
}

int main() {
    array<array<bool, DIM>, DIM> grille;

    for (auto& row : grille) {
        for (auto& val : row) {
            val = false;
        }
    }

    int x(0), y(0);
    char dir(' ');
    unsigned int len(0);

    while (true) {
        cout << "Entrez coord. x: ";
        cin >> x;
		if (x < 0) { break; }
        cout << "Entrez coord. y: ";
        cin >> y;
		if (y < 0) { break; }
        cout << "Entrez direction (N,S,E,O): ";
        cin >> dir;
        cout << "Entrez taille: ";
        cin >> len;

        cout << "Placement en (" << x << ", " << y << ") direction " << dir << " longueur " << len << " -> ";

        if (remplitGrille(grille, y, x, dir, len)) {
            cout << "succès";
        } else {
            cout << "échec";
        }
        cout << endl;
		// show_field(grille);
    }

    show_field(grille);
    /* Entrez coord. x: 2
    Entrez coord. y: 8
    Entrez direction (N,S,E,O): E
    Entrez taille: 2
    Placement en (2,8) direction E longueur 2 -> succès */

    return 0;
}
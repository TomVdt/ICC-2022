#include <iostream>
#include <vector>

using namespace std;

#define mat vector<vector<double>>

mat lire_matrice() {
	int l(0), c(0);
	cout << "Nombre de lignes: ";
	cin >> l;
	cout << "Nombre de colonnes: ";
	cin >> c;
	mat sortie(l, vector<double>(c));

	for (int i(0); i < l; ++i) {
		for (int j(0); j < c; ++j) {
			double tmp(0);
			cout << "M(" << i << "," << j << "): ";
			cin >> tmp;
			sortie[i][j] = tmp;
		}
	}

	return sortie;
}

void show_matrix(mat m) {
	for (auto ligne : m) {
		for (auto val : ligne) {
			cout << val << " ";
		}
		cout << endl;
	}
}

mat matmul(const mat& mat1, const mat& mat2) {
	int w(mat2[0].size());
	int h(mat1.size());
	mat result(h, vector<double>(w, 0.0));

	for (int ligne(0); ligne < h; ligne++) {
		for (int colonne(0); colonne < w; colonne++) {
			for (int i(0); i < mat1[0].size(); ++i) {
				result[ligne][colonne] += mat1[ligne][i] * mat2[i][colonne];
			}
		}
	}

	return result;
}

int main() {
	mat m1(lire_matrice());
	mat m2(lire_matrice());

	if (!m1.empty() && !m2.empty()) {
		// nombre de colonnes doit = nombre de lignes
		if (m1[0].size() != m2.size()) {
			cerr << "Pas possible de multiplier ca bro" << endl;
			return 1;
		}
	} else {
		cerr << "Y'a une matrice vide bro" << endl;
		return 1;
	}

	mat magik(matmul(m1, m2));
	cout << "Le résultat est" << endl;
	show_matrix(magik);
	cout << "bro" << endl;
	return 0;
}

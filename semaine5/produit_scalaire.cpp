#include <iostream>
#include <vector>

using namespace std;

double scalaire(vector<double> u, vector<double>v) {
	double s(0);
	for (int i(0); i < u.size(); ++i) {
		s += u[i] * v[i];
	}
	return s;
}

void fill_vector(vector<double>& v, int length, char name = 'v') {
	for (int i(0); i < length; ++i) {
		double tmp(0);
		cout << "Composante " << i << " de " << name << ": ";
		cin >> tmp;
		v.push_back(tmp);
	}
}

int main() {
	vector<double> v1;
	vector<double> v2;

	int n(0);
	cout << "Taille des vecteurs: ";
	cin >> n;

	fill_vector(v1, n, 'u');
	fill_vector(v2, n, 'v');

	cout << "Produit scalaire u·v = " << scalaire(v1, v2) << endl;

	return 0;
}
#include <iostream>

using namespace std;

int demander_annee() {
    int a(0);
    do {
        cout << "Entrez une annee (1583-4000) : ";
        cin >> a;
    } while (a > 4000 or a < 1583);
    return a;
}

void afficher_date(int annee, int jour) {
	cout << "Date de Paques en " << annee << " : ";
    if (jour <= 31) {
    	cout << jour << " mars" << endl;
    } else {
		cout << jour - 31 << " avril" << endl;
	}
}

int date_Paques(int annee) {
	int siecle(annee / 100);
	int p((13 + 8 * siecle) / 25);
	int q(siecle / 4);
	int M((15 - p + siecle - q) % 30);
	int N((4 + siecle - q) % 7);
	int d((M + 19 * (annee % 19)) % 30);
	int e((2 * (annee % 4) + 4 * (annee % 7) + 6 * d + N) % 7);
	int jour(e + d + 22);
	if (e == 6 && (d == 29 || (d == 28 && (11 * (M + 1)) % 30 < 19))) {
		jour -= 7;
	}
	return jour;
}

int main() {
    int annee(demander_annee());
	afficher_date(annee, date_Paques(annee));

	return 0;
}

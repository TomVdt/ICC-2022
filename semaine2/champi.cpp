#include <iostream>

using namespace std;

int main() {
    cout << "Pensez à un champignon : amanite tue-mouches, pied bleu, girolle," << endl
         << "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl
         << endl;

    int champi;
    bool lamelles, anneau, convexe, foret;
    cout << "Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ";
    cin >> convexe;

    if (convexe) {
        cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
        cin >> anneau;

        if (anneau) {
            cout << "Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ";
            cin >> foret;

            if (foret) {
                champi = 2;
            } else {
                champi = 1;
            }

        } else {
            champi = 6;
        }

    } else {
        cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
        cin >> anneau;

        if (anneau) {
            champi = 4;
        } else {
            cout << "Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ";
            cin >> lamelles;

            if (lamelles) {
                champi = 5;
            } else {
                champi = 3;
            }
        }
    }

    cout << "==> Le champignon auquel vous pensez est ";

    switch (champi) {
        case 1:
            cout << "l'agaric jaunissant";
            break;
        case 2:
            cout << "l'amanite tue-mouches";
            break;
        case 3:
            cout << "le cèpe de Bordeaux";
            break;
        case 4:
            cout << "le coprin chevelu";
            break;
        case 5:
            cout << "la girolle";
            break;
        case 6:
            cout << "le pied bleu";
            break;
    }
	cout << endl;
}
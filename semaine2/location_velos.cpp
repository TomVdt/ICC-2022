#include <iostream>
using namespace std;

int main() {
    cout << "Donnez l'heure de début de la location (un entier) : ";
    int debut;
    cin >> debut;

    cout << "Donnez l'heure de fin de la location (un entier) : ";
    int fin;
    cin >> fin;

    /*****************************************************
     * Compléter le code à partir d'ici
     *****************************************************/

    // Validation
    if (debut < 0 or debut > 24 or fin < 0 or fin > 24) {
        cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
        return -1;
    }

    int duree(fin - debut);

    if (duree == 0) {
        cout << "Bizarre, vous n'avez pas loué votre vélo bien longtemps !" << endl;
        return -1;
    }
    if (duree < 0) {
        cout << "Bizarre, le début de la location est après la fin ..." << endl;
        return -1;
    }

    int duree_plein(0);
    int duree_reduit(0);

    // trouver intersections
    // si intersection (calcul plein tarif)
    if (fin > 7 or debut < 17) {
        // limites de l'intersection
        int lower(7), upper(17);
        // mettre la limite basse à la plus grande des valeurs
        if (debut > lower) {
            lower = debut;
        }
        // ... et la limite haute à la plus petite
        if (fin < upper) {
            upper = fin;
        }

        if (upper - lower > 0) {
			// il y a une intersection
            duree_plein = upper - lower;
        }
    }

    // reste du temps est tarif réduit
    duree_reduit = duree - duree_plein;

    cout << "Vous avez loué votre vélo pendant" << endl;

    if (duree_reduit > 0) {
        cout << duree_reduit << " heure(s) au tarif horaire de "
             << 1 << " franc(s)" << endl;
    }
    if (duree_plein > 0) {
        cout << duree_plein << " heure(s) au tarif horaire de "
             << 2 << " franc(s)" << endl;
    }
    cout << "Le montant total à payer est de " << (2 * duree_plein) + duree_reduit
         << " franc(s)." << endl;

    /*******************************************
     * Ne rien modifier après cette ligne.
     *******************************************/

    return 0;
}

#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
  // Réduire le format d'affichage
  cout << setprecision(4);

  // Paramètres
  double taux_croissance_lapins(0.3);
  double taux_attaque(0.01);
  double taux_croissance_renards(0.008);
  double taux_mortalite(0.1);
  int duree(50);

  double renards_i(0.0);
  double lapins_i(0.0);

    /*****************************************************
     * Compléter le code à partir d'ici
     *****************************************************/

    // ===== PARTIE 1 =====
    // Saisie des populations initiales

    do {
        cout << "Combien de renards au départ (>= 2) ? ";
        cin >> renards_i;
    } while (renards_i < 2.0);

    do {
        cout << "Combien de lapins au départ  (>= 5) ? ";
        cin >> lapins_i;
    } while (lapins_i < 5.0);

    // ===== PARTIE 2 =====
    // Première simulation
    cout << endl
         << "***** Le taux d'attaque vaut " << taux_attaque * 100 << "%" << endl;

    double nb_renards(renards_i);
    double nb_lapins(lapins_i);

    for (int i(1); i <= duree; ++i) {
        double tmp(nb_lapins);
        nb_lapins *= (1.0 + taux_croissance_lapins - taux_attaque * nb_renards);
        
        /* if (nb_lapins < 0) {
            nb_lapins = 0;
        } else {
            nb_lapins = nb_lapins;
        }
        */
        // ternary expression
        
        nb_lapins = nb_lapins < 0 ? 0 : nb_lapins;

        nb_renards *= (1.0 + taux_attaque * tmp * taux_croissance_renards - taux_mortalite);
        nb_renards = nb_renards < 0 ? 0 : nb_renards;

        cout << "Après " << i << " mois, il y a " << nb_lapins << " lapins et " << nb_renards << " renards" << endl;
    }

    // ===== PARTIE 3 =====
    // Variation du taux d'attaque
    cout << endl;

    double taux_attaque_i(0), taux_attaque_f(0);

    do {
        cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
        cin >> taux_attaque_i;
    } while (taux_attaque_i < 0.5 or taux_attaque_i > 6.0);

    do {
        cout << "taux d'attaque à la fin  en % (entre " << taux_attaque_i << " et 6) ? ";
        cin >> taux_attaque_f;
    } while (taux_attaque_f < taux_attaque_i or taux_attaque_f > 6.0);

	taux_attaque_i /= 100;
	taux_attaque_f /= 100;
    cout << endl;

    taux_attaque = taux_attaque_i;
    while (taux_attaque < taux_attaque_f) {
        nb_renards = renards_i;
        nb_lapins = lapins_i;
        
        bool b_extinction_l(false);
        bool b_revive_l(false);
        bool b_extinction_r(false);
        bool b_revive_r(false);
        
        int i(0);
        while ((i < duree) && (nb_lapins > 0.0 || nb_renards > 0.0)) {
            double tmp(nb_lapins);
            nb_lapins *= (1.0 + taux_croissance_lapins - taux_attaque * nb_renards);
            nb_lapins = nb_lapins < 0 ? 0 : nb_lapins;
            nb_renards *= (1.0 + taux_attaque * tmp * taux_croissance_renards - taux_mortalite);
            nb_renards = nb_renards < 0 ? 0 : nb_renards;

            if (nb_renards < 5.0) {
                b_extinction_r = true;
            } else if (b_extinction_r) {
                b_revive_r = true;
            }
            if (nb_renards < 2.0) {
                nb_renards = 0;
            }

            if (nb_lapins < 5.0) {
                b_extinction_l = true;
            } else if (b_extinction_l) {
                b_revive_l = true;
            }
            if (nb_lapins < 2.0) {
                nb_lapins = 0;
            }

            ++i;
        }

        cout << "***** Le taux d’attaque vaut " << taux_attaque * 100 << " %" << endl;
        cout << "Après " << i << " mois, il y a " << nb_lapins << " lapins et " << nb_renards << " renards" << endl;

        if (b_extinction_r) {
            cout << "Les renards ont été en voie d'extinction" << endl;
        }
        if (b_revive_r) {
            cout << "mais la population est remontée ! Ouf !" << endl;
        }
        if (nb_renards < 2.0) {
            cout << "et les renards ont disparu :-(" << endl;
        }

        if (b_extinction_l) {
            cout << "Les lapins ont été en voie d'extinction" << endl;
        }
        if (b_revive_l) {
            cout << "mais la population est remontée ! Ouf !" << endl;
        }
        if (nb_lapins < 2.0) {
            cout << "et les lapins ont disparu :-(" << endl;
        }

        if (!(b_extinction_r or nb_renards < 2.0 or b_extinction_l or nb_lapins < 2.0)) {
            cout << "Les lapins et les renards ont des populations stables." << endl;
        }

        cout << endl;

        taux_attaque += 0.01;
    }
    /*******************************************
     * Ne rien modifier après cette ligne.
     *******************************************/

  return 0;
}
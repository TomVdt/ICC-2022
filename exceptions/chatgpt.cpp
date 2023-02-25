#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Déclaration des types Valeur et Liste
typedef int Valeur;
typedef vector<Valeur> Liste;

// Déclaration du type Somme_sous_liste
typedef struct {
    int debut;
    int fin;
    Valeur somme;
} Somme_sous_liste;

// Fonction tranche_max_1 qui trouve la sous-liste de somme maximale
// dans une séquence en utilisant un algorithme naïf
Somme_sous_liste tranche_max_1(const Liste& seq) {
    // Initialisation de la sous-liste à retourner
    Somme_sous_liste sousliste = {0, 0, numeric_limits<Valeur>::lowest()};
    // Boucle sur les débuts possibles de la sous-liste
    for (int debut = 0; debut < seq.size(); debut++) {
        // Boucle sur les fins possibles de la sous-liste
        for (int fin = debut; fin < seq.size(); fin++) {
            // Calcul de la somme de la sous-liste
            Valeur somme = 0;
            for (int pos = debut; pos <= fin; pos++) {
                somme += seq[pos];
            }
            // Mise à jour de la sous-liste si la somme est plus grande
            if (somme > sousliste.somme) {
                sousliste = {debut, fin, somme};
            }
        }
    }
    return sousliste;
}

Somme_sous_liste tranche_max_2(Liste liste) {
    // Initialisation de la tranche de somme maximale
    Somme_sous_liste tranche = {0, 0, numeric_limits<int>::min()};
    // Parcours des débuts possibles
    for (int debut = 0; debut < liste.size(); debut++) {
        // Parcours des fins possibles pour un début donné
        int somme = 0;
        for (int fin = debut; fin < liste.size(); fin++) {
            somme += liste[fin];
            // Mise à jour de la tranche de somme maximale si nécessaire
            if (somme > tranche.somme) {
                tranche = {debut, fin, somme};
            }
        }
    }
    return tranche;
}

Somme_sous_liste tranche_max_3(Liste liste) {
    // Initialisation de la tranche de somme maximale
    Somme_sous_liste tranche = {0, 0, numeric_limits<int>::min()};
    // Initialisation de la somme courante
    int somme = 0;
    // Initialisation du début de la tranche courante
    int debut = 0;
    // Parcours des fins possibles pour un début donné
    for (int fin = 0; fin < liste.size(); fin++) {
        // Mise à jour de la somme courante
        somme += liste[fin];
        // Mise à jour de la tranche de somme maximale si nécessaire
        if (somme > tranche.somme) {
            tranche = {debut, fin, somme};
        }
        // Si la somme courante est négative ou nulle, on recommence la tranche courante juste après l'élément courant
        if (somme <= 0) {
            debut = fin + 1;
            somme = 0;
        }
    }
    return tranche;
}

int main() {
    // Déclaration des séquences de test
    vector<Liste> seq({{11, 13, -4, 3, -26, 7, -13, 25, -2, 17, 5, -8, 1},
                       {},
                       {-3, -4, -1, -2, -3},
                       {-1, -4, -3, -2, -3},
                       {3, 4, 1, 2, -3},
                       {3, 4, 1, 2, 3},
                       {3, -1, -1, -1, 5},
                       {-5, -4, 1, 1, 1}});
    // Test de la fonction tranche_max_1 sur chaque séquence
    for (int i = 0; i < seq.size(); i++) {
        Somme_sous_liste tranche;
        if (seq[i].empty()) {
            tranche = {0, 0, 0};
        } else {
            tranche = tranche_max_3(seq[i]);
        }
        cout << "La tranche de somme maximale pour la liste [";
        for (int j = 0; j < seq[i].size(); j++) {
            cout << seq[i][j];
            if (j < seq[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "] est [";
        if (!seq[i].empty()) {
            for (int j = tranche.debut; j <= tranche.fin; j++) {
                cout << seq[i][j];
                if (j < tranche.fin) {
                    cout << ", ";
                }
            }
        }
        cout << "] avec une somme de " << tranche.somme << "." << endl;
    }
    return 0;
}
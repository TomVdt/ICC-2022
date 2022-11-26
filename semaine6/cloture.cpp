#include <iostream>
#include <vector>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

typedef vector<vector<int>> Carte;

struct Position {
  int i;
  int j;
};

bool binaire(Carte const& carte) {
  for (auto ligne : carte) {
    for (auto val : ligne) {
      if (!(val == 1 or val == 0)) {
        return false;
      }
    }
  }
  return true;
}

bool valide(Carte const& carte, Position const& pos) {
  if (0 <= pos.j && pos.j < carte.size()) {
    if (0 <= pos.i && pos.i < carte[0].size()) {
      return true;
    }
  }
  return false;
}

void affiche(Carte const& carte) {
  for (auto ligne : carte) {
    for (auto val : ligne) {
      cout << val;
    }
    cout << endl;
  }
  cout << "----" << endl;
}

bool contient(vector<int> const& ensemble, int valeur) {
  for (auto val : ensemble) {
    if (val == valeur) {
      return true;
    }
  }
  return false;
}

void ajoute_unique(vector<int>& ensemble, int valeur) {
  if (!contient(ensemble, valeur)) {
    ensemble.push_back(valeur);
  }
}

int lfind(vector<int> const& ensemble, int valeur) {
  int i(0);
  while (i < ensemble.size() && ensemble[i] != valeur) {
    i++;
  }
  return i;
}

int rfind(vector<int> const& ensemble, int valeur) {
  int j(ensemble.size() - 1);
  while (j >= 0 && ensemble[j] != valeur) {
    j--;
  }
  return j;
}

bool convexite_lignes(Carte& carte, vector<int> const& labels_bords) {
  for (int j(0); j < carte.size(); j++) {
    int l(lfind(carte[j], 1));
    int r(rfind(carte[j], 1));
    for (int i(l); i < r; i++) {
      if (carte[j][i] != 1 && contient(labels_bords, carte[j][i])) {
        cout << "Votre carte du terrain n'est pas convexe par lignes :" << endl;
        cout << "bord extérieur entrant trouvé en position [";
        cout << j << "][" << i;
        cout << "]" << endl;
        return false;
      }
    }
  }
  return true;
}

void marque_composantes(Carte& carte) {
  vector<Position> stack;
  int composante(1);

  for (int j(0); j < carte.size(); j++) {
    for (int i(0); i < carte[0].size(); i++) {
      if (carte[j][i] == 0) {
        composante++;
        stack.push_back({i, j});

        while (!stack.empty()) {
          Position pos = stack[stack.size() - 1];
          stack.pop_back();

          if (carte[pos.j][pos.i] == 0) {
            carte[pos.j][pos.i] = composante;

            Position directions[4] = { {pos.i - 1, pos.j}, {pos.i + 1, pos.j}, {pos.i, pos.j - 1}, {pos.i, pos.j + 1} };
            for (int k(0); k < 4; k++) {
              if (valide(carte, directions[k])) {
                stack.push_back(directions[k]);
              }
            }
          }
        }
      }
    }
  }
}

bool convexite_lignes(Carte& carte) {
  marque_composantes(carte);

  // Parcourir les bords
  vector<int> labels;
  int w(carte[0].size());
  int h(carte.size());
  // haut et bas
  for (int i(0); i < w; i++) {
    if (carte[0][i] != 1) {
      ajoute_unique(labels, carte[0][i]);
    }
    if (carte[h - 1][i] != 1) {
      ajoute_unique(labels, carte[h - 1][i]);
    }
  }
  // gauche et droite
  for (int i(0); i < h; i++) {
    if (carte[i][0] != 1) {
      ajoute_unique(labels, carte[i][0]);
    }
    if (carte[i][w - 1] != 1) {
      ajoute_unique(labels, carte[i][w - 1]);
    }
  }

  return convexite_lignes(carte, labels);
}

bool verifie_et_modifie(Carte& carte) {
  if (!binaire(carte)) {
    cout << "Votre carte du terrain ne contient pas que des 0 et des 1." << endl;
    return false;
  }

  if (!convexite_lignes(carte)) {
    return false;
  }

  int longueur_etang(0);
  int prev(0);
  for (int j(0); j < carte.size(); j++) {
    for (int i(0); i < carte[0].size(); i++) {

      if (prev == 1 && carte[j][i] != 0) {
        int k(i + 1);
        while (k < carte[0].size()) {
          // si on retrouve du terrain après etre rentré dans l'eau
          if (carte[j][k] == 1) {
            longueur_etang = k - i;
            break;
          }
          k++;
        }
      }
      prev = carte[j][i];

      if (longueur_etang) {
        carte[j][i] = 1;
        // on a avancé dans l'etang
        longueur_etang--;
      }
    }
    // pas oublier de réinitialiser le mode étang pour chaque ligne
    longueur_etang = 0;
    // ... et la valeur précédente
    prev = 0;
  }

  return true;
}

int voisins(Carte const& carte, Position& pos) {
  int nb(0);
  if (valide(carte, {pos.i-1, pos.j})) {
    nb += carte[pos.j][pos.i-1] != carte[pos.j][pos.i];
  } else {
    // on considère le bord comme un voisin "different"
    nb++;
  }
  if (valide(carte, {pos.i+1, pos.j})) {
    nb += carte[pos.j][pos.i+1] != carte[pos.j][pos.i];
  } else {
    nb++;
  }
  if (valide(carte, {pos.i, pos.j-1})) {
    nb += carte[pos.j-1][pos.i] != carte[pos.j][pos.i];
  } else {
    nb++;
  }
  if (valide(carte, {pos.i, pos.j+1})) {
    nb += carte[pos.j+1][pos.i] != carte[pos.j][pos.i];
  } else {
    nb++;
  }
  return nb;
}

double longueur_cloture(Carte const& carte, double echelle = 2.5) {
  int clotures(0);
  for (int j(0); j < carte.size(); j++) {
    for (int i(0); i < carte[0].size(); i++) {
      if (carte[j][i] == 1) {
        Position pos = { i, j };
        clotures += voisins(carte, pos);
      }
    }
  }
  return clotures * echelle;
}

void strings_bro() {

}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  cout << "Carte au départ :" << endl;
  affiche(carte);
  if (verifie_et_modifie(carte)) {
    cout << "Carte après modification :" << endl;
    affiche(carte);
    cout << "Il vous faut " << longueur_cloture(carte)
         << " mètres de clôture pour votre terrain."
         << endl;
  }

  return 0;
}

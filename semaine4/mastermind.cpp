#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
                                                    * all compilers seems to support it :-( */

char tirer_couleur()
{
  static const char* const couleurs = ".RGBCYM";
  static const int nb = strlen(couleurs) - 1;

  return couleurs[distribution(generateur,
                               std::uniform_int_distribution<int>::param_type {0, nb})];
}

// ======================================================================
char poser_question()
{
  char lu(' ');
  cout << "Entrez une couleur : ";
  cin >> lu;
  return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
  char lu(poser_question());
  while (not couleur_valide(lu)) {
    cout << "'" << lu << "' n'est pas une couleur valide." << endl;
    cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << endl;
    lu = poser_question();
  }
  return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
  cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
  while (nb-- > 0) {
    cout << c;
  }
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
                   char r1, char r2, char r3, char r4)
{
  afficher_couleurs(c1, c2, c3, c4);
  cout << " : ";
  afficher_reponses(c1, c2, c3, c4,
                    r1, r2, r3, r4);
  cout << endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
  cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
  cout << "Perdu :-(" << endl;
  cout << "La bonne combinaison était : ";
  afficher_couleurs(c1, c2, c3, c4);
  cout << endl;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

// ======================================================================
bool couleur_valide(char c)
{
  return c == '.' || c == 'R' || c == 'G' || c == 'B' || c == 'C' || c == 'Y' || c == 'M';
}

// ======================================================================
bool verifier(char c1, char& r1, int& score
             )
{
  if (c1 == r1) {
    score++;
    r1 = 'x';
    return true;
  } else {
    return false;
  }
}

// ======================================================================
void apparier(char c, char& r1, char& r2, char& r3, int& score
             )
{
  if (verifier(c, r1, score)) {
    return;
  } else if (verifier(c, r2, score)) {
    return;
  } else if (verifier(c, r3, score)) {
    return;
  }
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4)
{
  int correct(0);
  int dedans(0);
  
  bool b_c1(verifier(c1, r1, correct));
  bool b_c2(verifier(c2, r2, correct));
  bool b_c3(verifier(c3, r3, correct));
  bool b_c4(verifier(c4, r4, correct));

  if (!b_c1) {
    apparier(c1, r2, r3, r4, dedans);
  }
  if (!b_c2) {
    apparier(c2, r1, r3, r4, dedans);
  }
  if (!b_c3) {
    apparier(c3, r1, r2, r4, dedans);
  }
  if (!b_c4) {
    apparier(c4, r1, r2, r3, dedans);
  }

  // Afficher les resultats
  afficher(correct, '#');
  afficher(dedans, '+');
  afficher(4 - dedans - correct, '-');
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
           char r1, char r2, char r3, char r4)
{
  return c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4;
}

// ======================================================================
void jouer(int coups_max = 8
          )
{
  char r1(tirer_couleur());
  char r2(tirer_couleur());
  char r3(tirer_couleur());
  char r4(tirer_couleur());

  char c1('x');
  char c2('x');
  char c3('x');
  char c4('x');

  int nb_coups(0);

  do {
    c1 = lire_couleur();
    c2 = lire_couleur();
    c3 = lire_couleur();
    c4 = lire_couleur();

    afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);

    nb_coups++;
  } while (!gagne(c1, c2, c3, c4, r1, r2, r3, r4) && nb_coups < coups_max);

  if (gagne(c1, c2, c3, c4, r1, r2, r3, r4)) {
    message_gagne(nb_coups);
  } else {
    message_perdu(r1, r2, r3, r4);
  }
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  jouer();
  return 0;
}

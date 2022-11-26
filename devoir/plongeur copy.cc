#include <iostream>
#include <string>
#include <cmath>    // pour exp()
using namespace std;

// ======================================================================

// Types et constantes
struct Conditions {
  double profondeur;
  double vitesse;
  double temps;
};

struct Diver {
  string nom;
  double masse;
  double volume;
  double acceleration;
  Conditions conditions;
};

struct Status {
  bool profondeur_atteinte;
  bool vitesse_max_atteinte;
  bool balon_gonfle;
};

constexpr double g(9.81);


// Prototypes

void display(const Diver& d);
void dive(Diver d);
void evolve(Diver& d, const Conditions& conditions_initiales);
void message(const Diver& d, const string& mess, double valeur, const string& unitees);
void update_status(Diver& d, Conditions& conditions_initiales, Status& status);


// Implémentations

// Affiche les données du plongeur (temps, profondeur, vitesse, acceleration)
void display(const Diver& d) {
  cout << d.conditions.temps << ", "
       << d.conditions.profondeur<< ", "
       << d.conditions.vitesse << ", "
       << d.acceleration << endl;
}

// Affiche un message pour un certain état donné
void message(const Diver& d, const string& mess, double valeur, const string& unitees) {
  cout << "## (t = "
       << d.conditions.temps << " s) "
       << d.nom << " "
       << mess << " ("
       << valeur << " "
       << unitees << ")"
       << endl;
}

// Boucle principale de la simulation
void dive(Diver d) {
  // Vérification des données d'entrée
  // Une masse négative ou nulle n'est pas possible dans la simulation et n'a
  // pas beaucoup de sens physique
  if (d.masse <= 0) {
    cerr << "La masse du plongeur ne peut pas être négative ou nulle!" << endl;
    return;
  }
  // Pareil pour le volume
  if (d.volume <= 0) {
    cerr << "Le volume du plongeur ne peut pas être négatif ou nul!" << endl;
    return;
  }
  // L'accélération est mise à jour dans `evolve`, sa valeur initiale n'a pas
  // d'importance puisqu'elle est seulement utilisée après dans un appel à
  // `update_status`

  // Vérification de conditions initiales cohérentes
  // Si le plongeur est au dessus de l'eau dans les conditions initiales, on peut:
  // - soit mettre un message d'erreur et arreter le programme
  // - soit supposer qu'il ne plonge pas / est déjà sorti,
  // - soit qu'il fait une chute libre verticale, augmentant sa vitesse initiale
  //   d'entrée dans l'eau, ce que l'on peut trouver avec un peu de physique.
  // Optons pour le choix amusant avec une chute libre dans l'eau.
  
  /*
            |          <-- v0, h = profondeur, t = t0

                           ↑ axe y

      ~~~~~~~~~~~~~~   <-- On cherche ti (temps d'impact)
                           et v0_i quand profondeur = 0
  
    Projection selon y
    v0 = -v0 y
    g = -g y
    h = h y

    => acceleration = -g
    => vitesse = -g(t - t0) - v0
    => "profondeur" = -g/2 (t - t0)² - v0(t - t0) + h

    => ti - t0 = -(v0 ± √(v0² + 2gh)) / g
  
    On retient la solution plus grande (on avance dans le temps)
    Selon y:
    => vitesse(ti) = -√(v0² + 2gh)
  
    On en déduit:
    => v0_i = -vitesse(ti) = √(v0² + 2gh)
  */

  if (d.conditions.profondeur > 0) {
    const double& v0(d.conditions.vitesse);
    const double sqrt_delta(sqrt(v0 * v0 + 2 * g * d.conditions.profondeur));
    const double t_impact(-(v0 - sqrt_delta) / g);

    // Mettre à jour les conditions initiales
    d.conditions.profondeur = 0.0;
    d.conditions.temps = t_impact;
    // on a v0_impact = sqrt_delta
    d.conditions.vitesse = sqrt_delta;
  }

  // Si sa vitesse initiale est < 0 (il monte), c'est possible que le plongeur
  // monte avant de redescendre et atteigne la surface de l'eau, sans avoir
  // gonflé son balon. Il devrait ensuite couler (si sa masse et son volume sont
  // cohérents). On ne doit donc pas afficher le message de "remontée" s'il
  // atteint la surface sans être descendu à -43 m et sans avoir gonflé le balon

  // Le temps peut prendre n'importe quelle valeur initialement car on ne
  // considère que les écarts de temps (t0 - t) (bien sûr dans les limites du
  // type `double`)

  // Copie des conditions du plongeur pour les conditions initiales
  Conditions conditions_initiales(d.conditions);

  // Marqueurs pour l'évolution de la simulation
  Status status( {false, false, false} );

  // TODO: revoir conditions d'arret: s'il saute de l'eau avant de plonger?
  do {
    display(d);
    evolve(d, conditions_initiales);
    update_status(d, conditions_initiales, status);
  } while (!status.balon_gonfle || d.conditions.profondeur < 0.0);
}

// Calculs pour l'évolution des parametres du plongeur
void evolve(Diver& d, const Conditions& conditions_initiales) {
  ++d.conditions.temps;

  // TODO: alias nécessaires?
  // Des alias pour alleger les formules
  const double& p0(conditions_initiales.profondeur);
  const double& v0(conditions_initiales.vitesse);
  const double& t0(conditions_initiales.temps);

  // Quelques constantes qui apparaissent plusieurs fois dans les formules
  const double dt(t0 - d.conditions.temps);
  const double mu(1.0 - 1000.0 * (d.volume / d.masse));
  const double alpha(exp(dt));
  const double k(v0 - g * mu);

  // Application des formules
  d.conditions.vitesse = (alpha * k) + (g * mu);
  d.acceleration = -(alpha * k);
  d.conditions.profondeur = p0 + (k * (alpha - 1)) + (dt * g * mu);
}

// Met à jour l'état et affiche des messages quand certaines conditions sur la plongée sont atteints
void update_status(Diver& d, Conditions& conditions_initiales, Status& status) {
  if (!status.vitesse_max_atteinte && d.acceleration < 1e-5) {
    status.vitesse_max_atteinte = true;
    message(d, "a atteint sa vitesse maximale", d.acceleration, "ms-2");
  }
  if (!status.profondeur_atteinte && d.conditions.profondeur < -40.0) {
    status.profondeur_atteinte = true;
    message(d, "a atteint la profondeur desirée", d.conditions.profondeur, "m");
  }
  if (!status.balon_gonfle && d.conditions.profondeur < -43.0) {
    status.balon_gonfle = true;
    // Nouvelles conditions "initiales"
    d.volume += 0.0375;
    conditions_initiales.profondeur = d.conditions.profondeur;
    conditions_initiales.vitesse = 0.0;
    conditions_initiales.temps = d.conditions.temps;
    message(d, "s’arrête et gonfle son balon", d.conditions.profondeur, "m");
  }
  // TODO: Vraiment seulement si le balon est gonflé?
  if (status.balon_gonfle && d.conditions.profondeur >= 0.0) {
    message(d, "est de retour à la surface", d.conditions.profondeur, "m");
  }
}


// ======================================================================
// Ce main() NE DOIT PAS ÊTRE MODIFIÉ !
// int main() {
//   Diver jacques({ "Jacques"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 0} });
//   dive(jacques);
//   return 0;
// }

void annoncer_test(const Diver& d) {
  cout << d.nom << "(m="
       << d.masse << ", v="
       << d.volume << ", acc="
       << d.acceleration << ") plonge avec conditions profondeur "
       << d.conditions.profondeur << ", vitesse "
       << d.conditions.vitesse << ", temps "
       << d.conditions.temps << endl;
}

void test(Diver d) {
  annoncer_test(d);
  dive(d);
  cout << endl;
}

int main() {
  cout << "Normal" << endl;
  test({"Jacques"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 0}});

  cout << "Masses et volumes chelous" << endl;
  test({ "Michel"s, 0.0, 0.075, 0.0, {-1.2, 0.8, 0} });
  test({ "Michel"s, 90.0, 0.0, 0.0, {-1.2, 0.8, 0} });

  cout << "Conditions initiales cheloues" << endl;
  cout << "En hauteur" << endl;
  test({ "Michel"s, 90.0, 0.075, 0.0, {1.2, 0.8, 0} });
  test({ "Michel"s, 90.0, 0.075, 0.0, {3, -0.8, 0} });

  cout << "Vitesse haute, sous l'eau" << endl;
  test({ "Michel"s, 90.0, 0.075, 0.0, {-1.2, 5.0, 0} });

  // TODO
  // S'il sort de l'eau: fini? replonge?
  // Si en plus un saut, on ne peut pas appliquer les formules
  // habituelles...
  test({ "Michel"s, 90.0, 0.075, 0.0, {-1.2, -5.0, 0} });

  cout << "t0 != 0" << endl;
  test({ "Michel"s, 90.0, 0.075, 0.0, {-1.2, 0.8, -32} });
  test({ "Michel"s, 90.0, 0.075, 0.0, {-1.2, 0.8, 69} });
  
  // TODO
  // S'il flotte naturellement?
  // Si le balon n'est pas suffisant?

  return 0;
}
